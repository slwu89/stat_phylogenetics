################################################################################
#       __  __               __                   ____  ____
#      / / / /___ __      __/ /_____  _____      / __ )/ __ \
#     / /_/ / __ `/ | /| / / //_/ _ \/ ___/_____/ __  / / / /
#    / __  / /_/ /| |/ |/ / ,< /  __(__  )_____/ /_/ / /_/ /
#   /_/ /_/\__,_/ |__/|__/_/|_|\___/____/     /_____/_____/
#
#   Conditional simulation of Hawkes Birth-death processes with exponential excitation function
#   December 2018
#   Sean Wu
#
################################################################################

rm(list=ls());gc()

# input parameters
tmax <- 1000
alpha <- 0.9 # rate of offspring generation
beta <- 1/5 # 1/mean lifespan
mu <- 2e-16 # rate of homogeneous Poisson arrivals
maxN <- 2e3 # maximum cap on number of nodes, break loop for memory

# the root node has an id=0 and ancestor=-1L
# ancestor=-1L means that node is an immigration event

# set of active nodes
id <- 0L
Z <- rexp(n=1,rate=beta)
active <- data.frame(time=0.0,Z=Z,id=id,ancestor=-1L)

# set of all nodes
tree <- data.frame(time=0.0,Z=Z,id=id,ancestor=-1L)

tnow <- 0.0 # current simulation time


# run simulation
while(tnow < tmax){
  
  # filter active nodes
  living_nodes <- which((tnow - active$time) <= active$Z)
  active <- active[living_nodes,]
  
  # find out what happens
  # take into account the special case where all nodes have died
  n <- length(living_nodes) # number of active nodes
  if(n == 0){
    
    b_times <- 2e16
    b_min <- 1L
    i_time <- rexp(n = 1,rate = mu)
    
  } else {
    
    b_times <- rexp(n = n,rate = alpha*beta)
    
    # filter out birth times that occur after the residual lifespan of the nodes is over
    b_reject <- which(b_times > ((active$time + active$Z) - tnow))
    b_times[b_reject] <- 2e16 # virtually guaranteed that immigration will be first
    
    b_min <- which.min(b_times)
    i_time <- rexp(n = 1,rate = mu)
    
  }
  
  # immigration occurs
  if(i_time < b_times[b_min]){
    
    tnow <- tnow + i_time
    if(tnow > tmax){break()}
    Z <- rexp(n=1,rate=beta) # sample mark
    id <- id + 1L
    
    active <- rbind(active,data.frame(time = tnow,Z = Z,id = id,ancestor = -1L))
    tree <- rbind(tree,data.frame(time = tnow,Z = Z,id = id,ancestor = -1L))
    
    # birth occurs
  } else {
    
    tnow <- tnow + b_times[b_min]
    if(tnow > tmax){break()}
    Z <- rexp(n=1,rate=beta) # sample mark
    id <- id + 1L
    
    a_id <- active[b_min,"id"] # id of ancestor
    active <- rbind(active,data.frame(time = tnow,Z = Z,id = id,ancestor = a_id))
    tree <- rbind(tree,data.frame(time = tnow,Z = Z,id = id,ancestor = a_id))
    
  }
  
  if(id >= maxN){
    break()
  }
  
}

tree

nodes <- data.frame(name=tree$id)
edges <- data.frame()
for(i in 2:nrow(tree)){
  edges <- rbind(edges,data.frame(from = tree[i,"ancestor"],to = tree[i,"id"]))
}

library(igraph)
tree_ig <- graph_from_edgelist(as.matrix(edges+1), directed = TRUE)
tree_ig1 <- layout_as_tree(graph = tree_ig,root = 1L)
tree_igd <- dominator_tree(tree_ig,root=1)
plot.igraph(tree_igd$domtree,layout=layout_as_tree(tree_igd$domtree,root=1),
            vertex.size = 5)

# simple non-markovian BD process
hawkesBD_simple <- function(mu,alpha,beta,tmax,maxN){
  
  n <- 1L # begin simulation with one existing point
  t <- 0.0 # current time
  
  # the joint process (point process of times and associated state process)
  X <- matrix(c(t,n),byrow = T,nrow = 1,ncol = 2,dimnames = list(NULL,c("time","N"))) 
  
  # birth event state-dependent intensity function
  b_intensity <- function(mu,alpha,beta,n){
    mu + (alpha*beta*n)
  }
  
  # death event state-dependent intensity function
  d_intensity <- function(beta,n){
    beta*n
  }
  
  # simulate until reach tmax or reach absorbing state of 0
  while((t < tmax) & (n > 0)){
    
    lambda <- b_intensity(mu,alpha,beta,n)
    mu <- d_intensity(beta,n)
    
    rate <- lambda+mu # sum of rates is total rate to any event
    t <- t + rexp(n=1,rate=rate) 
    
    # birth
    if(runif(1) < lambda/rate){
      
      n <- n + 1L
      X <- rbind(X,c(t,n))
      
    # death
    } else {
      
      n <- n - 1L
      X <- rbind(X,c(t,n))
      
    }
    
    # killswitch to avoid processes running away to infinity
    if(n > maxN){
      break()
    }
    
  }
  
  return(X)
}

sample0 <- function(x, ...){
  return(
    x[sample.int(length(x), ...)]
  )
}


# non-markovian bd process with marks (above is averaging out wrt Q)
hawkesBD_marked <- function(mu,alpha,beta,tmax,maxN){
  
  n <- 1L # begin simulation with one existing point
  t <- 0.0 # current time
  id <- 0L
  
  # the joint process (point process of times and associated state process)
  X <- matrix(c(t,n),byrow = T,nrow = 1,ncol = 2,dimnames = list(NULL,c("time","N")))
  
  # the marked point process of arrivals
  Z <- rexp(n = 1,rate = beta)
  M <- matrix(c(t,Z,id,-1),byrow = T,nrow = 1,ncol = 4,dimnames = list(NULL,c("time","Z","id","Anc")))
  M_hist <- M
  
  # birth event state-dependent intensity function
  b_intensity <- function(alpha,beta,n){
    (alpha*beta*n)
  }
  
  # calculate cardinality of set of living points
  card_n <- function(M,t){
    c <- 0L
    for(i in 1:nrow(M)){
      if((M[i,"time"] < t) & (sum(M[i,c("time","Z")]) >=  t)){
        c <- c + 1L
      }
    }
    return(c)
  }
  
  # simulate until reach tmax or reach absorbing state of 0
  while((t < tmax) & (n > 0)){
    
    N <- card_n(M,t)
    lambda <- b_intensity(alpha,beta,N)
    
    lifespans <- apply(X = M[,c("time","Z"),drop = FALSE],MARGIN = 1,FUN = sum)
    next_d <- which.min(lifespans)
    
    t_b <- t + rexp(n = 1,rate = mu+lambda) # time of next birth
    t_d <- lifespans[next_d] # time of next death
    
    # birth
    if(t_b < t_d){
      
      id <- id + 1L
      
      if(runif(1) < mu / (mu + lambda)){
        anc <- -1L
      } else {
        anc_i <- sample0(x = 1:N,size = 1L,replace = FALSE)
        anc <- M[anc_i,"id"]
      }
      
      
      n <- n + 1L
      Z <- rexp(n = 1,rate = beta)
      pt <- c(t_b,Z,id,anc)
      
      M <- rbind(M,pt)
      M_hist <- rbind(M_hist,pt)
      t <- t_b
      
    } else {
      
      n <- n - 1L
      M <- M[-next_d,,drop=FALSE]
      t <- t_d
      
    }

    X <- rbind(X,c(t,n))
    
    # killswitch to avoid processes running away to infinity
    if(n > maxN){
      break()
    }
    
  }
  
  return(
    list("M"=M_hist,"X"=X)
  )
}


X_simple <- hawkesBD_simple(mu = 1,alpha = 0.05,beta = 2,tmax = 20,maxN = 1e3)
plot(stepfun(x = X_simple[,"time"],y = c(0,X_simple[,"N"])),
     xlim=c(0,X_simple[nrow(X_simple),"time"]),
     main = "Simple Hawkes-BD Process",
     xlab = "Time",ylab = "N(t)")


X_marked <- hawkesBD_marked(mu = 0.05,alpha = 0.95,beta = 1/20,tmax = 100,maxN = 1e3)
X_marked$M

library(igraph)
iArrows <- igraph:::igraph.Arrows
library(viridis)

par(mfrow=c(1,2))

plot(stepfun(x = X_marked$X[,"time"],y = c(0,X_marked$X[,"N"])),
     xlim=c(0,X_marked$X[nrow(X_marked$X),"time"]),
     main = "Marked Hawkes-BD Process",
     xlab = "Time",ylab = "N(t)")

ymax <- ceiling(max(apply(X = X_marked$M,MARGIN = 1,FUN = sum)))
xmax <- ceiling(max(X_marked$M[,"time"]))
plot(x = X_marked$M[,"time"],y = X_marked$M[,"time"],
     ylim = c(-2,ymax),pch = 16,
     main = "Marks and Lifespans of Particles",
     xlab = "Arrival Time",
     ylab = "Marks (Lifespans)")
# draw lifespans
segments(x0 = X_marked$M[,"time"],y0 = X_marked$M[,"time"],
         x1 = X_marked$M[,"time"],y1 = rowSums(X_marked$M),
         col = "firebrick3",lwd=1.25)
# draw relationships
offspring <- X_marked$M[X_marked$M[,"Anc"] != -1,]
a_colors <- data.frame(id=as.integer(X_marked$M[X_marked$M[,"Anc"] == -1,"id"]),
                       col=as.character(viridis(n = sum(X_marked$M[,"Anc"] == -1),end = 0.75)),stringsAsFactors = F)
for(i in 1:nrow(offspring)){
  a_i <- offspring[i,"Anc"]
  a_pt <- X_marked$M[X_marked$M[,"id"] == a_i,]
  iArrows(a_pt["time"], a_pt["time"],
          offspring[i,"time"], offspring[i,"time"],
          h.lwd=0.5, sh.lwd=2,
          sh.col=a_colors[a_colors$id == a_i,"col"],
          curve=-1.5, width=2, size=0.25)
}

par(mfrow=c(1,1))
