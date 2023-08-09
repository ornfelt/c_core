# READ FILE
OUTLAND = 1
TRICKERER_SQL = 1

def read_lines_from_file(file_name):
  with open(file_name) as file:
      node_lines = [line.rstrip() for line in file]
      #print(node_lines)
      return node_lines

node_vertices = {}
node_zones = {}
node_lines = read_lines_from_file("trickerer_outland_northrend.sql") if TRICKERER_SQL else read_lines_from_file("2023_06_09_00_creature_template_npcbot_wander_nodes.sql")
#node_lines = read_lines_from_file("testing.sql") if TRICKERER_SQL else read_lines_from_file("2023_06_09_00_creature_template_npcbot_wander_nodes.sql")
node_map_id = "530" if OUTLAND else "571"
# Loop nodes
for line in node_lines:
  if len(line) > 0 and line[0] == '(':
    map_id = line.split(",")[2]
    if map_id == node_map_id:
      node_id = line.split('(')[1].split(',')[0]
      #print(node_id)
      #node_links = line.split("'")[3].replace(":0", "")
      #node_links = node_links.rstrip(node_links[-1]).split(" ")
      node_links = line.split("'")[3].replace(":0", "")[:-1].split(" ")
      #print(node_links)
      node_vertices[node_id] = node_links
      # Also add zone_ids
      zone_id = line.split(",")[3]
      node_zones[node_id] = zone_id

from collections import defaultdict

# This class represents a directed graph using adjacency list representation
class Graph:
  def __init__(self):
    # Default dictionary to store graph
    self.graph = defaultdict(list)
    self.found_targets = defaultdict(set)
    self.node_history = defaultdict(list)
    self.used_found_targets_count = 0
    self.curr_start_id = 0
    self.should_print = False

  def addEdge(self, u, v):
    self.graph[u].append(v)

  def DFSUtil(self, v, visited, target_v):
    # Mark the current node as visited and print it
    visited.add(v)
    if v not in self.node_history[self.curr_start_id] and v != self.curr_start_id:
      self.node_history[self.curr_start_id].append(v)

    if v == target_v:
      if self.should_print:
        print(v, end=" ")
        print("Target found!")
      self.target_found = True
      #self.found_targets[target_v].update(visited)
      self.found_targets[target_v] = self.found_targets[target_v].union(visited)
      return
    elif not self.target_found:
      if self.should_print:
        print(v, end=" ")
      # Recur for all the vertices adjacent to this vertex
      for neighbour in self.graph[v]:
        if neighbour not in visited:
          self.DFSUtil(neighbour, visited, target_v)

  def DFS_search(self, start_id, target_id):
    if self.should_print:
      print("start_id:", start_id, "\ntarget_id:", target_id)
    self.curr_start_id = start_id
    visited = set()
    # First check found_targets
    if target_id in self.found_targets.keys() and start_id in self.found_targets[target_id]:
      #print(f"Target {target_id} already found from start_id {start_id}")
      self.used_found_targets_count += 1
      return True
    elif len(self.node_history[start_id]) > 0:
      if target_id in self.found_targets.keys():
        for start_node in self.node_history[start_id]:
          if start_node == target_id or start_node in self.found_targets[target_id]:
            return True
      else:
        start_id = self.node_history[start_id][-1]
        visited = set(self.node_history[start_id])

    self.target_found = False
    for vertex in self.graph.copy()[start_id]:
    #for vertex in self.graph[start_id]:
      if vertex not in visited and not self.target_found:
        self.DFSUtil(vertex, visited, target_id)
      if self.target_found:
        return self.target_found

    return self.target_found

#if __name__ == "__main__":
g = Graph()
for node_id, node_links in node_vertices.items():
  #print(node_id, node_links)
  for link in node_links:
    g.addEdge(int(node_id), int(link))

g.should_print = True
# Search all
print("\nLooping all nodes... Nodes:", len(node_vertices.values()))
loop_counter = 0
loop_counter_one = 0
#g.should_print = False
links_to_all = True
# Dicts are ordered in Pythhon >= 3.7, so we can iterate over the keys like below
# We can also randomize dict order to potentially get better results
can_reach = g.DFS_search(2418, 3579) # Hf -> Netherstorm
print(can_reach)
can_reach = g.DFS_search(2418, 2860) # Hf -> Nagrand
print(can_reach)
can_reach = g.DFS_search(2418, 3649) # Hf -> Shadowmoon
print(can_reach)

g.should_print = False
for node_id in node_vertices.keys():
  for other_node_id in node_vertices.keys():
    node_id = int(node_id)
    other_node_id = int(other_node_id)
    if node_id != other_node_id:
      can_reach = g.DFS_search(node_id, other_node_id)
      loop_counter += 1
      if not can_reach:
        print("CAN'T REACH:", other_node_id, "FROM NODE:", node_id)
        links_to_all = False
        break
  else:
    continue # Only executed if the inner loop did NOT break
  break # Only executed if the inner loop DID break

node_node_count = len(node_vertices.values())
print("Done checking links... loop_counter:", loop_counter, "- should be", node_node_count,"*",node_node_count-1," = ",node_node_count*(node_node_count-1))
#assert loop_counter == node_node_count * (node_node_count-1)
print("used_found_targets_count:", g.used_found_targets_count)
