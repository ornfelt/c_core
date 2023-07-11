# Author: Jonas Örnfelt

#Welcome to block world!
#How space is represented in block world:
#	     Col0 Col1 Col2
# Row 0 [0,0][0,1][0,2]
# Row 1 [1,0][1,1][1,2]
# Row 2 [2,0][2,1][2,2]

StartState = [['','',''],['','C',''],['B','A','']] # from the top down
GoalState = [['','','A'],['','','B'],['','','C']] # from the top down
CurrentState = StartState #Should be called at the start of a task

# Environment console visualization
#try it out using print_environment(CurrentState)
def print_environment(environment):
	environmentString = '' #empty placeholder for the string
	for i in range(len(environment)): #loop through the columns
		for j in range(len(environment[i])): #loop through the rows in the column
			if (environment[i][j]): #check if there is an element
				environmentString += environment[i][j] #if so, add element to string
			else:
				environmentString += "∵" #Otherwise, fill it with empty space 
			if j == 2: #If its the last row (index 2) ->
				environmentString += "\n" #make a line break
	print(environmentString) #print environment


# RandomStartState generator
# try it out with print(RandomStartState()) or print_environment(RandomStartState())
import random
def RandomStartState():
	SState = [['','',''],['','',''],['','','']] #create empty state
	blockList = ['A','B','C'] #list of blocks
	while len(blockList) > 0:
		a = random.randint(0,len(blockList)-1) #get random int from list of blocks
		randomPos = random.randint(0,2) #get a random number betwen 0-2
		if SState[2][randomPos]: #check if there is a block at random position at bottom
			if SState[1][randomPos]: #check if there is a block at same position in the middle
				SState[0][randomPos] = blockList[a] #if so, place block on top instead
			else:
				SState[1][randomPos] = blockList[a] #if not, place block in the middle instead
		else:
			SState[2][randomPos] = blockList[a] #If not, place block at bottom
		blockList.pop(a) #remove block from list
	return SState

# Write function or functions for the arm!
def pickUpBlockAt(row, column):
  if CurrentState[row][column]: # Check if there is a block available for picking up
    if row == 2 and (CurrentState[0][column] or CurrentState[1][column]):  # Check if there is blocks above
      return None
    elif row == 1 and CurrentState[0][column]:  # Check if there is blocks above
      return None
    else:
      return CurrentState[row][column]
  else:
    return None

def dropBlockAt(row, column, block):
    if is_free(row, column):
      if row == 0 and CurrentState[2][column] == '' and CurrentState[1][column] == '':
        CurrentState[2][column] = block
      elif row == 0 and CurrentState[1][column] == '':
        CurrentState[1][column] = block
      elif row == 1 and CurrentState[2][column] == '':
        CurrentState[2][column] = block
      else:
        CurrentState[row][column] = block
      return True
    return False

# Check if column is occupied
def is_free(r, c):
  # if return is true, slot is available
  for i in range(r+1):
    if CurrentState[i][c]:
      return False
  return True

# Check if game won
def check_win():
  return CurrentState == GoalState

# Return true if successful operation
def operate_arm(r1, c1, r2, c2):
  if r1 == r2 and c1 == c2:
    return False
  #print(f"Attempting to move: {r1},{c1} to {r2}, {c2}\n")
  curr_block = pickUpBlockAt(r1,c1)
  if curr_block:
    #print_environment(CurrentState)
    CurrentState[r1][c1] = '' # Remove block from prev location
    if dropBlockAt(r2,c2, curr_block):
      return True
    else:
      CurrentState[r1][c1] = curr_block # Add block again to prev location
      #print_environment(CurrentState)
      return False
  else:
    return False

print("0,0  0,1  0,2\n1,0  1,1  1,2\n2,0  2,1, 2,2\n") # Informative print
# Solution for first StartState:
operate_arm(1,1,2,2)
operate_arm(2,0,1,2)
operate_arm(2,1,0,2)
if check_win():
  print("Game won!")
  print_environment(CurrentState)

StartState = [['', '', ''], ['', 'A', ''], ['B', 'C', '']]
CurrentState = StartState
operate_arm(1,1,1,0)
operate_arm(2,1,2,2)
operate_arm(1,0,2,1)
operate_arm(2,0,1,2)
operate_arm(2,1,0,2)
if check_win():
  print("Game won!")
  print_environment(CurrentState)

StartState = [['', '', 'B'], ['', '', 'A'], ['', '', 'C']]
CurrentState = StartState

operate_arm(0,2,2,0)
operate_arm(1,2,2,1)
operate_arm(2,0,1,2)
operate_arm(2,1,0,2)
if check_win():
  print("Game won!")
  print_environment(CurrentState)

def find_index(char):
  for sub_list in CurrentState:
    if char in sub_list:
      return [CurrentState.index(sub_list), sub_list.index(char)]


def solve_game():
  solve_c()
  solve_b()
  a_index = find_index('A')
  operate_arm(a_index[0], a_index[1], 0, 2) # Move A to correct pos
  if check_win():
    #print("Game won!")
    #print_environment(CurrentState)
    pass

def solve_c():
  c_index = find_index('C')
  if (c_index[0] == 2 and c_index[1] == 2):
    return
  else:
    # Fix C...
    if operate_arm(c_index[0], c_index[1], 2, 2): # Try to just move it to the right pos
      return
    # Remove all blocks from col2
    if CurrentState[0][2]:
      if not operate_arm(0,2,2,0):
        if not operate_arm(0,2,1,0):
          operate_arm(0,2,2,1)
    if CurrentState[1][2]:
      if not operate_arm(1,2,2,0):
        if not operate_arm(1,2,1,0):
          operate_arm(1,2,2,1)
    if CurrentState[2][2]:
      if not operate_arm(2,2,2,0):
        if not operate_arm(2,2,1,0):
          operate_arm(2,2,2,1)

    c_index = find_index('C')
    # If any blocks above C, then move those to other column
    if operate_arm(c_index[0], c_index[1], 2, 2): # First try to just move it to the right pos (works if on top (row:0))
      return
    if c_index[1] == 0: # If C is in first col
      if CurrentState[0][0] and CurrentState[0][0] != 'C':
        if not operate_arm(0,0,2,1):
          operate_arm(0,0,1,1)
      if CurrentState[1][0] and CurrentState[1][0] != 'C':
        if not operate_arm(1,0,2,1):
          operate_arm(1,0,1,1)

      c_index = find_index('C')
      if operate_arm(c_index[0], c_index[1], 2, 2): # Try to move C to right pos
        return

    if c_index[1] == 1: # If C is in second col
      if CurrentState[0][1] and CurrentState[0][1] != 'C':
        if not operate_arm(0,1,2,0):
          operate_arm(0,1,1,0)
      if CurrentState[1][1] and CurrentState[1][1] != 'C':
        if not operate_arm(1,1,2,0):
          operate_arm(1,1,1,0)
      c_index = find_index('C')
      if operate_arm(c_index[0], c_index[1], 2, 2): # Try to move C to right pos
        return

def solve_b():
  b_index = find_index('B')
  if (b_index[0] == 1 and b_index[1] == 2):
    return
  else:
    # Fix B...
    if operate_arm(b_index[0], b_index[1], 1, 2): # Try to just move it to the right pos
      return
    # Remove all blocks from col2 (row 0 and 1)
    if CurrentState[0][2]:
      if not operate_arm(0,2,2,0):
        if not operate_arm(0,2,1,0):
          operate_arm(0,2,2,1)
    if CurrentState[1][2]:
      if not operate_arm(1,2,2,0):
        if not operate_arm(1,2,1,0):
          operate_arm(1,2,2,1)

    b_index = find_index('B')
    # If any blocks above B, then move those to other column
    if operate_arm(b_index[0], b_index[1], 1, 2): # First try to just move it to the right pos (works if on top (row:0))
      return
    if b_index[1] == 0: # If B is in first col
      if CurrentState[0][0] and CurrentState[0][0] != 'B':
        if not operate_arm(0,0,2,1):
          operate_arm(0,0,1,1)
      if CurrentState[1][0] and CurrentState[1][0] != 'B':
        if not operate_arm(1,0,2,1):
          operate_arm(1,0,1,1)
      b_index = find_index('B')
      if operate_arm(b_index[0], b_index[1], 1, 2): # Try to move B to right pos
        return
    if b_index[1] == 1: # If B is in second col
      if CurrentState[0][1] and CurrentState[0][1] != 'B':
        if not operate_arm(0,1,2,0):
          operate_arm(0,1,1,0)
      if CurrentState[1][1] and CurrentState[1][1] != 'B':
        if not operate_arm(1,1,2,0):
          operate_arm(1,1,1,0)
      b_index = find_index('B')
      if operate_arm(b_index[0], b_index[1], 1, 2): # Try to move B to right pos
        return

new_state = RandomStartState()
print_environment(new_state)
CurrentState = new_state
solve_game()

#print("Solving 1 million states...")
games_solved = 0

#for i in range(100000): # 100k (takes 1 sec)
#for i in range(1000000): # 1 million (takes 5-10 secs)
for i in range(10000000): # 10 million (takes 2-3 mins)
    new_state = RandomStartState()
    #print_environment(new_state)
    CurrentState = new_state
    solve_game()
    games_solved += 1
print(f"Solved {games_solved} games!")