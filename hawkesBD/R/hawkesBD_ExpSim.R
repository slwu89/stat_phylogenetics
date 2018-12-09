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
tmax <- 10
alpha <- 0.9 # rate of offspring generation
beta <- 10 # 1/mean lifespan
mu <- 1 # rate of homogeneous Poisson arrivals
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
    Z <- rexp(n=1,rate=beta) # sample mark
    id <- id + 1L

    active <- rbind(active,data.frame(time = tnow,Z = Z,id = id,ancestor = -1L))
    tree <- rbind(tree,data.frame(time = tnow,Z = Z,id = id,ancestor = -1L))

  # birth occurs
  } else {

    tnow <- tnow + b_times[b_min]
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
