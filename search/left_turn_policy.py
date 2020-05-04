# ----------
# User Instructions:
# 
# Implement the function optimum_policy2D below.
#
# You are given a car in grid with initial state
# init. Your task is to compute and return the car's 
# optimal path to the position specified in goal; 
# the costs for each motion are as defined in cost.
#
# There are four motion directions: up, left, down, and right.
# Increasing the index in this array corresponds to making a
# a left turn, and decreasing the index corresponds to making a 
# right turn.

forward = [[-1,  0], # go up
           [ 0, -1], # go left
           [ 1,  0], # go down
           [ 0,  1]] # go right
forward_name = ['up', 'left', 'down', 'right']

# action has 3 values: right turn, no turn, left turn
action = [-1, 0, 1]
action_name = ['R', '#', 'L']

# EXAMPLE INPUTS:
# grid format:
#     0 = navigable space
#     1 = unnavigable space 
grid = [[1, 1, 1, 0, 0, 0],
        [1, 1, 1, 0, 1, 0],
        [0, 0, 0, 0, 0, 0],
        [1, 1, 1, 0, 1, 1],
        [1, 1, 1, 0, 1, 1]]

init = [4, 3, 0] # given in the form [row,col,direction]
                 # direction = 0: up
                 #             1: left
                 #             2: down
                 #             3: right
                
goal = [2, 0] # given in the form [row,col]

cost = [2, 1, 20] # cost has 3 values, corresponding to making 
                  # a right turn, no turn, and a left turn

# EXAMPLE OUTPUT:
# calling optimum_policy2D with the given parameters should return 
# [[' ', ' ', ' ', 'R', '#', 'R'],
#  [' ', ' ', ' ', '#', ' ', '#'],
#  ['*', '#', '#', '#', '#', 'R'],
#  [' ', ' ', ' ', '#', ' ', ' '],
#  [' ', ' ', ' ', '#', ' ', ' ']]
# ----------

# ----------------------------------------
# modify code below
# ----------------------------------------


def optimum_policy2D(grid,init,goal,cost):

    q_values = [[[[999 for _ in range(len(action))] for _ in range(4)] for row in range(len(grid[0]))] for col in range(len(grid))]
    policy = [[' ' for row in range(len(grid[0]))] for col in range(len(grid))]
    
    change = True
    while change:
        change = False

        for x in range(len(grid)):
            for y in range(len(grid[0])):
                for theta in range(4):
                    for a in range(len(action)):
                        if goal[0] == x and goal[1] == y:
                            if q_values[x][y][theta][a] > 0:
                                q_values[x][y][theta][a] = 0
                                change = True
                                policy[x][y]='*'

                        elif grid[x][y] == 0:
                            theta2 = (theta + action[a])%4
                            x2 = x + forward[theta2][0]
                            y2 = y + forward[theta2][1]

                            if x2 >= 0 and x2 < len(grid) and y2 >= 0 and y2 < len(grid[0]) and grid[x2][y2] == 0:
                                v2 = min(q_values[x2][y2][theta2]) + cost[a]

                                if v2 < q_values[x][y][theta][a]:
                                    change = True
                                    q_values[x][y][theta][a] = v2
    state = init
    while state[:2]!=goal:
        x = state[0]
        y = state[1]
        theta = state[2]
        
        a = q_values[x][y][theta].index(min(q_values[x][y][theta]))
        policy[x][y] = action_name[a]
        theta2 = (theta + action[a])%4
        x2 = x + forward[theta2][0]
        y2 = y + forward[theta2][1]
        
        state = [x2,y2,theta2]
        
    return policy
    
policy = optimum_policy2D(grid,init,goal,cost)

for row in policy:
    print(row)