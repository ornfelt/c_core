# Author: Jonas Örnfelt
""" 
1.
"""
import random
import numpy as np
import matplotlib.pyplot as plt
 
# Probability to move right or left
prob = [0.5, 0.5] 
# Start position (2 makes sense for the plot)
start = 2 
# Add start position
positions = [start]
# The random points
rndm = np.random.random(10)
right_prob = rndm < prob[0]
left_prob = rndm > prob[1]
#print(f"rp: {right_prob}")
#print(f"lp: {left_prob}")
 
for right, left in zip(right_prob, left_prob):
    if left:
      print("Going left")
    else:
      print("Going right")

    positions.append(positions[-1] - right + left)
 
# Plotting graph of the random walk in 1D
print(f"Final positions: {positions}")
plt.plot(positions)
plt.show()


""" 
2.
"""
import random
import numpy as np
import matplotlib.pyplot as plt

start = 0
positions = [start]
c = 1
for i in range(10):
  leftp = 1 - (0.5 + (0.5 * (positions[-1] / (c + abs(positions[-1])))))
  rightp = 1 - leftp
  #print(f"leftp: {leftp}")
  #print(f"rightp: {rightp}")

  # Random points
  rndm = np.random.random(1)
  left_prob = rndm < leftp
  right_prob = [not left_prob]

  #print(f"left_prob: {left_prob}")
  #print(f"right_prob: {right_prob}")
  for right, left in zip(right_prob, left_prob):
    if left:
      print("LEFT")
    else:
      print("RIGHT")
    #print(f"Appending: {positions[-1] - right + left}")
    positions.append(positions[-1] - right + left)
 
# Plot
print(f"Final positions: {positions}")
plt.plot(positions)
plt.show()


""" 
3.
"""
import numpy as np
import random as rm
import time

# Cities
cities = ["Uppsala", "Malmö"]
# Statespaces
states = ["Sunny","Rainy"]
# Events
transitionName = [["SuSu","SuRa"],["RaRa","RaSu"]]
# Probabilities matrix (transition matrix)
transitionMatrix = [[0.9,0.1],[0.5,0.5]]

# Check that probabilities sum to 1
if sum(transitionMatrix[0])+sum(transitionMatrix[1]) != 2:
    print("Error!!!! Probabilities MUST ADD TO 1. Check transition matrix!!")
    raise ValueError("Probabilities MUST ADD TO 1")

# Use Markov model to forecast the weather
def weatherForecast(days):
    for x in range(2):
      # Start Sunny in Uppsala
      print(f"Weather in {cities[x]}:")
      #weatherToday = rm.choice(states)
      weatherToday = states[x]
      i = 0
      print("Starting weather: ", weatherToday)
      while i < days:
          if weatherToday == "Sunny":
              #numpy.random.choice(a, size=None, replace=True, p=None)
              change = np.random.choice(transitionName[0],replace=True,p=transitionMatrix[0])
              if change == "SuSu":
                  pass
              else:
                  weatherToday = "Rainy"
          elif weatherToday == "Rainy":
              change = np.random.choice(transitionName[1],replace=True,p=transitionMatrix[1])
              if change == "RaRa":
                  pass
              else:
                  weatherToday = "Sunny"
          print(weatherToday)
          i += 1
          time.sleep(0.2)

# Forecast for 10 days
weatherForecast(10)


""" 
4.
"""
import numpy as np
import itertools
from itertools import permutations
import statistics
import matplotlib.pyplot as plt

def PlayArm1():
  return np.random.randint(10,60) #TOP-SECRET
def PlayArm2():
  return np.random.randint(12,50) #TOP-SECRET
def PlayArm3():
  return np.random.randint(18,25) #TOP-SECRET
def PlayArm4():
  return np.random.randint(-20,100) #TOP-SECRET
def PlayArm5():
  return np.random.randint(-100,150) #TOP-SECRET

score_step_tracker = []
ACTIONS = {1: PlayArm1, 2: PlayArm2, 3: PlayArm3, 4: PlayArm4, 5: PlayArm5}

class Game(object):
    def __init__(self):
        self.score = 0
        self.steps = 0
        self.new_score = 0

    def update_game(self, action):
        # Get score
        self.new_score = ACTIONS[action]()
        #print(f"New points: {self.new_score}")
        self.score += self.new_score
        self.steps += 1 # add steps

    def get_reward(self):
        return self.give_reward()

    def give_reward(self):
        if len(score_step_tracker) == 1:
          pass
        if len(score_step_tracker) > 5 and self.score > max(score_step_tracker):
          return 1
        elif self.score > statistics.mean(score_step_tracker):
          return 0
        else:
          return -1
		  
class Agent(object):
    def __init__(self, alpha=0.15, random_factor=0.2): # 80% explore, 20% exploit
        self.alpha = alpha
        self.randomFactor = random_factor
        print(f"Random factor: {self.randomFactor}")
        self.action_history = [] # action, reward
        self.G = {}
        self.init_reward()
        print(f"Self.G: {self.G}")

    def init_reward(self):
        for i in ACTIONS:
          self.G[i] = np.random.uniform(low=1.0, high=0.1)
    
    def choose_action(self):
        maxG = -10e15
        next_move = None
        randomN = np.random.random()
        if randomN < self.randomFactor:
            # if random number below random factor, choose random action
            next_move = np.random.choice([1,2,3,4,5])
        else:
            # if exploiting, gather all possible actions and choose one with the highest G (reward)
            for action in ACTIONS:
                if self.G[action] >= maxG:
                    next_move = action
                    maxG = self.G[action]

        return next_move

    def update_action_history(self, action, reward):
        self.action_history.append(action)
        self.action_history.append(reward)

    def learn(self):
        target = 0
        rew_action = self.action_history[0]
        reward = self.action_history[1]
        #self.G[prev] = self.G[prev] + self.alpha * (target - self.G[prev])
        self.G[rew_action] += reward
        target += reward

        self.action_history = []
        self.randomFactor -= 10e-5 # Decrease randomFactor after each game session
		
		
score_step_tracker = []

if __name__ == '__main__':
    game = Game()
    robot = Agent(alpha=0.1, random_factor=0.15)
    action_list = []
    score_tracker = []
    final_score = 0
    temp_score = 0

    for i in range(10000):
        if game.steps == 0:
          action = robot.choose_action() # choose an action (explore or exploit)
        action_list.append(action)
        game.update_game(action) # update the game according to the action
        score_tracker.append(game.new_score)

        if game.steps > 50:
          final_score += game.score
          temp_score = game.score
          score_step_tracker.append(temp_score)
          temp_score = 0
          # Score after 50 tries
          print(f"SCORE: {score_step_tracker[-1]}, ACTION: {action}")
          reward = game.get_reward()
          robot.update_action_history(action, reward) # Update agent memory with action and reward
          robot.learn() # robot learns after 50 tries
          game = Game()

    # Print and plot results
    print(f"Final score: {final_score}")
    plt.hist(action_list)
    plt.show()
    plt.semilogy(score_step_tracker, "b--")
    plt.show()
    plt.semilogy(score_tracker, "b--")
    plt.show()
