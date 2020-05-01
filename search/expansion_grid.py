# -----------
# User Instructions:
# 
# Modify the function search so that it returns
# a table of values called expand. This table
# will keep track of which step each node was
# expanded.
#
# Make sure that the initial cell in the grid 
# you return has the value 0.
# ----------

grid = [[0, 0, 1, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 1, 0, 1, 0],
        [0, 0, 1, 0, 1, 0],
        [0, 0, 1, 0, 1, 0]]
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
    # modify code below
    # ----------------------------------------
    expand = [[-1 for _ in y] for y in grid]
    expand[init[0]][init[1]] = 0
    
    frontier = [[init[0],init[1],0]]
    explored = set()
    
    count = 0
    while len(frontier)!=0:
        node = frontier[0]
        del frontier[0]
        g = node[2]
        node = tuple(node[0:2])
        
        if goal==list(node):
            expand[node[0]][node[1]] = count
            return expand
        
        if not node in explored:
            expand[node[0]][node[1]] = count
            count+=1
            
            children = get_children(node,grid)

            for child in children:
                frontier.append([child[0], child[1], g+cost])

            explored.add(node)
        
    return expand

expand = search(grid,init,goal,cost)
print(expand)