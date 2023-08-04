"""
Assignment 2.3
Author: Jonas Örnfelt
"""

import numpy as np
import random

ACTIONS = {'U': (-1, 0), 'D': (1, 0), 'L': (0, -1), 'R': (0, 1)}

class MazeGame(object):
    def __init__(self, env):
        self.set_env(env)
        self.robot_position = self.start_pos
        self.steps = 0
        self.construct_allowed_states()

    def find_val(self, mylist, char):
        for sub_list in mylist:
            if char in sub_list:
                return (mylist.index(sub_list), sub_list.index(char))

    """
      Set maze environment
      P = 1 = Pit
      A = 2 = Robot start position
      G = 3 = Goal
    """
    def set_env(self, env):
        self.block_pos = []
        self.start_pos = self.find_val(env, 'A')
        self.win_pos = self.find_val(env, 'G')
        self.environment = np.zeros((4, 4))

        for y, row in enumerate(env):
            for x, col in enumerate(row):
                if env[y][x] == 'P':
                    self.block_pos.append((y,x))

        for i in self.block_pos:
            self.environment[i[0],i[1]] = 1

        self.environment[self.start_pos] = 2
        self.environment[self.win_pos] = 3

    def is_allowed_move(self, state, action):
        # Check allowed move from a given state
        y, x = state
        y += ACTIONS[action][0]
        x += ACTIONS[action][1]
        if y < 0 or x < 0 or y > 3 or x > 3:
            # If robot moves off board
            return False
        return True

    # Set allowed states
    def construct_allowed_states(self):
        allowed_states = {}
        for y, row in enumerate(self.environment):
            for x, col in enumerate(row):
                allowed_states[(y,x)] = []
                for action in ACTIONS:
                    if self.is_allowed_move((y,x), action) & (action != 0):
                        allowed_states[(y,x)].append(action)
                        #print("new allowedStates: ", action, "for state: ", y, x)   
        self.allowed_states = allowed_states

    # Update maze - set new robot pos and increase steps
    def update_maze(self, action):
        # Current position
        y, x = self.robot_position
        # New position
        y += ACTIONS[action][0]
        x += ACTIONS[action][1]
        self.robot_position = (y, x)
        self.steps += 1

    # Check if game over
    def is_game_over(self):
        # Check if robot in the final position or if it has fallen into pit
        if self.robot_position == self.win_pos:
            return True
        else:
            return False

    # Get state and reward
    def get_state_and_reward(self):
        return self.robot_position, self.give_reward()

    # Give reward based on pos
    def give_reward(self):
        # If won give 1 reward
        if self.robot_position == self.win_pos:
            return 1
        elif self.environment[self.robot_position] == 1:
          return -3
        else: 
          return -1
		  
class Agent(object):
    def __init__(self, states, epsilon=0.3):
        self.state_history = [((0, 0), 0)] # state, reward
        self.e = epsilon
        self.annealingSteps = 200
        self.eMin = 0.01
        self.q_table = {}
        self.init_reward(states)

    # Initial reward values
    def init_reward(self, states):
        for i, row in enumerate(states):
            for j, col in enumerate(row):
                self.q_table[(j, i)] = np.random.uniform(low=1.0, high=0.1)
    
    # Choose action (exploit or random)
    def choose_action(self, state, allowedMoves):
        maxG = -10e15
        next_move = None
        randomN = np.random.random()
        if randomN < self.e:
            # Choose random action
            next_move = np.random.choice(allowedMoves)
        else:
            # if exploiting, gather all possible actions and choose one with the highest G (reward)
            for action in allowedMoves:
                new_state = tuple([sum(x) for x in zip(state, ACTIONS[action])])
                if self.q_table[new_state] >= maxG:
                    next_move = action
                    maxG = self.q_table[new_state]

        return next_move

    # Update state history with reward
    def update_state_history(self, state, reward):
        self.state_history.append((state, reward))

    # Teach robot
    def learn(self):
        target = 0
        gamma = 0.8
        learning_rate = 0.3
        rew_list = []

        for prev, reward in reversed(self.state_history):
            self.q_table[prev] = self.q_table[prev] + learning_rate * (target - self.q_table[prev])
            target += reward

        # Reset state history and decrease e
        self.state_history = []
        if self.e > self.eMin:
          self.e = self.e - ((1 - self.eMin) / self.annealingSteps)
		  
		  
import numpy as np
import matplotlib.pyplot as plt

def RandomEnvironment():
    environment = [['','','',''],['','','',''],['','','',''],['','','','']]
    elementList = ['G','A','P','P'] #list of elements to place out
    while len(elementList) > 0:
      x = random.randint(0,len(environment)-1) #rand x pos
      y = random.randint(0,len(environment)-1) #rand y pos
      while environment[x][y]: #while something IS there
        x = random.randint(0,len(environment)-1) #get new ones
        y = random.randint(0,len(environment)-1) #get new ones
      environment[x][y] = elementList.pop(0) #pops the element and returns it
    return environment

def print_environment(environment):
    environmentString = '' #empty placeholder for the string
    for i in range(len(environment)): #loop through the columns
        for j in range(len(environment[i])): #loop through the rows in the column
            if (environment[i][j]): #check if there is an element
                environmentString += environment[i][j] #if so, add element to string
            else:
                environmentString += "∵" #Otherwise, fill it with empty space
            if j == 3: #If its the last row (index 2) ->
                environmentString += "\n" #make a line break
    print(environmentString) #print environment
    return environmentString #print environment

ExampleEnvironment = [['','','','A'],['','','P','P'],['','','',''],['','','','G']]
#print_environment(ExampleEnvironment)
curr_environment = ExampleEnvironment
#curr_environment = RandomEnvironment()

if __name__ == '__main__':
    maze = MazeGame(curr_environment)
    print(maze.environment)
    print(f"Allowed_states: {maze.allowed_states}\n")
    robot = Agent(maze.environment, epsilon=1)
    moveHistory = []
    final_action_list = []
    
    for i in range(2000):
        while not maze.is_game_over():
            # Get state
            state, _ = maze.get_state_and_reward()
            # Choose explore or exploit action 
            action = robot.choose_action(state, maze.allowed_states[state])
            # Print last set of actions
            if i == 999:
              #print(action)
              final_action_list.append(action)
            maze.update_maze(action) # update the maze according to the action
            # Update state and reward
            state, reward = maze.get_state_and_reward()
            robot.update_state_history(state, reward)
            # If robot falls into pit, reset position
            if maze.environment[maze.robot_position] == 1:
                maze.robot_position = maze.start_pos
        
        # Teach robot after reach game
        robot.learn()
        moveHistory.append(maze.steps) # Append amounts of steps to move history
        maze = MazeGame(curr_environment) # Restart game

left_arrow = u'\u2190'
up_arrow = u'\u2191'
right_arrow = u'\u2192'
down_arrow = u'\u2193'
ACTION_ARR = {'U': up_arrow, 'D': down_arrow, 'L': left_arrow, 'R': right_arrow}
ACTION_POS = {'U': -5, 'D': 5, 'L': -1, 'R': 1}

def print_solution(environment, action_list):
    environment_string = '' #empty placeholder for the string
    for i in range(len(environment)): #loop through the columns
        for j in range(len(environment[i])): #loop through the rows in the column
            if (environment[i][j]): #check if there is an element
                environment_string += environment[i][j] #if so, add element to string
            else:
                environment_string += "∵" #Otherwise, fill it with empty space
                #environment_string += ":" #Otherwise, fill it with empty space
            if j == 3: #If its the last row (index 2) ->
                environment_string += "\n" #make a line break
    print(environment_string)
    environment_string = list(environment_string)

    print(f"Solution actions: {' '.join(final_action_list)}: ")
    # Print solution
    a_pos = environment_string.index('A')
    curr_pos = a_pos
    for action in action_list:
      curr_pos += ACTION_POS[action]
      #if environment_string[curr_pos] != 'G':
      environment_string[curr_pos] = ACTION_ARR[action]
    environment_string = ' '.join(environment_string)
    # Fix ugly spaces
    environment_string = environment_string[:9] + environment_string[9 + 1:]
    environment_string = environment_string[:18] + environment_string[18 + 1:]
    environment_string = environment_string[:27] + environment_string[27 + 1:]
    print(environment_string) # print solution

#print_solution(ExampleEnvironment, ["L", "L", "D" ,"D" ,"R" ,"D" ,"R"])
print_solution(curr_environment, final_action_list)

# Plot amount of actions through iterations
#plt.semilogy(moveHistory, "b--")
#plt.show()