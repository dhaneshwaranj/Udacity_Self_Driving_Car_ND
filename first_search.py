# ----------
# User Instructions:
# 
# Define a function, search() that returns a list
# in the form of [optimal path length, row, col]. For
# the grid shown below, your function should output
# [11, 4, 5].
#
# If there is no valid path from the start point
# to the goal, your function should return the string
# 'fail'
# ----------

# Grid format:
#   0 = Navigable space
#   1 = Occupied space


grid = [[0, 0, 1, 0, 0, 0],
        [0, 0, 1, 0, 0, 0],
        [0, 0, 0, 0, 1, 0],
        [0, 0, 1, 1, 1, 0],
        [0, 0, 0, 0, 1, 0]]
init = [0, 0]
goal = [len(grid)-1, len(grid[0])-1]
cost = 1

delta = [[-1, 0], # go up
         [ 0,-1], # go left
         [ 1, 0], # go down
         [ 0, 1]] # go right

delta_name = ['^', '<', 'v', '>']


def get_children(node,grid):
    children = []
    for x in delta:
        row = min(max(node[0]+x[0],0),len(grid)-1)
        col = min(max(node[1]+x[1],0),len(grid[0])-1)
        
        if grid[row][col]==0:
            children.append([row,col])
    return children
    
    
def search(grid,init,goal,cost):
    # ----------------------------------------
    # insert code here
    # ----------------------------------------
    frontier = [[init[0],init[1],0]]
    explored = set()
    
    path = 'fail'
    
    while len(frontier)!=0:
        node = frontier[0]
        del frontier[0]
        g = node[2]
        node = tuple(node[0:2])
        
        if goal==list(node):
            path = [g,len(grid)-1,len(grid[0])-1]
            return path
        
        if not node in explored:
            children = get_children(node,grid)

            for child in children:
                frontier.append([child[0], child[1], g+cost])

            explored.add(node)
        
    return path

path = search(grid,init,goal,cost)
print(path)
