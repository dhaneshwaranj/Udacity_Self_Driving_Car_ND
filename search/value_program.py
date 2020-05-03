# ----------
# User Instructions:
# 
# Create a function compute_value which returns
# a grid of values. The value of a cell is the minimum
# number of moves required to get from the cell to the goal. 
#
# If a cell is a wall or it is impossible to reach the goal from a cell,
# assign that cell a value of 99.
# ----------

grid = [[0, 1, 0, 0, 0, 0],
        [0, 1, 0, 0, 0, 0],
        [0, 1, 0, 0, 0, 0],
        [0, 1, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0]]
goal = [len(grid)-1, len(grid[0])-1]
cost = 1 # the cost associated with moving from a cell to an adjacent one

delta = [[-1, 0 ], # go up
         [ 0, -1], # go left
         [ 1, 0 ], # go down
         [ 0, 1 ]] # go right

delta_name = ['^', '<', 'v', '>']


def get_children(node,grid):
    children = []
    for x in delta:
        row = min(max(node[0]+x[0],0),len(grid)-1)
        col = min(max(node[1]+x[1],0),len(grid[0])-1)
        
        if grid[row][col]==0:
            children.append([row,col])
    return children

def compute_value(grid,goal,cost):
    # ----------------------------------------
    # insert code below
    # ----------------------------------------
    
    # make sure your function returns a grid of values as 
    # demonstrated in the previous video.
    
    values = [[99 for _ in y] for y in grid]
    values[goal[0]][goal[1]] = 0
    
    frontier = [[goal[0],goal[1],0]]
    explored = set()
    
    while len(frontier)!=0:
        node = frontier[0]
        del frontier[0]
        v = node[2]
        node = tuple(node[0:2])
        
        if not node in explored:
            values[node[0]][node[1]] = v
            
            children = get_children(node,grid)
        
            for child in children:
                frontier.append([child[0], child[1], v+cost])
        
            explored.add(node)
    
    
    return values

values = compute_value(grid,goal,cost)
for row in values:
    print(row)