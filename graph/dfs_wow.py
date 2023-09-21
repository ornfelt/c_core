import re

def read_lines_from_file(filename):
    with open(filename, 'r') as file:
        return file.readlines()

class ContinentID:
    EasternKingdoms = 0
    Kalimdor = 1
    Outland = 530
    Northrend = 571

# Settings and global vars
TRICKERER_SQL = 0
continent = ContinentID.EasternKingdoms

def contains(c, e):
    return e in c

class Graph:
    def __init__(self):
        self.graph = {}
        self.node_history = {}
        self.curr_start_id = 0
        self.target_found = False
        self.found_targets = {}
        self.should_print = False

    def addEdge(self, u, v):
        if u not in self.graph:
            self.graph[u] = []
        self.graph[u].append(v)

    def DFSUtil(self, v, visited, target_v):
        visited.add(v)
        if v not in self.node_history.get(self.curr_start_id, []) and v != self.curr_start_id:
            if self.curr_start_id not in self.node_history:
                self.node_history[self.curr_start_id] = []
            self.node_history[self.curr_start_id].append(v)

        if v == target_v:
            if self.should_print:
                print(f"{v} Target found!")
            self.target_found = True
            if target_v not in self.found_targets:
                self.found_targets[target_v] = set()
            self.found_targets[target_v].update(visited)
            return
        elif not self.target_found:
            if self.should_print:
                print(v, end=" ")
            for neighbour in self.graph.get(v, []):
                if neighbour not in visited:
                    self.DFSUtil(neighbour, visited, target_v)

    def DFS_search(self, start_id, target_id):
        if self.should_print:
            print(f"start_id: {start_id}, target_id: {target_id}")
        self.curr_start_id = start_id
        visited = set()

        if target_id in self.found_targets and start_id in self.found_targets[target_id]:
            return True
        elif start_id in self.node_history:
            if target_id in self.found_targets:
                for start_node in self.node_history[start_id]:
                    if start_node == target_id or start_node in self.found_targets[target_id]:
                        return True
            else:
                start_id = self.node_history[start_id][-1]
                if start_id in self.node_history:  # Check if start_id exists in node_history before updating visited
                    visited.update(self.node_history[start_id])

        self.target_found = False
        for vertex in self.graph.get(start_id, []):
            if vertex not in visited and not self.target_found:
                self.DFSUtil(vertex, visited, target_id)

            if self.target_found:
                return True
        return self.target_found

def extract_index(input_str, sep, idx):
    return input_str.split(sep)[idx]

isolated_nodes = [
    (3923, 3936),
    (3959, 3978),
    (4087, 4103),
    (4746, 4789),
    (4790, 4854)
]

def isIsolatedNodes(node_id, other_node_id):
    for node_range in isolated_nodes:
        if node_id >= node_range[0] and node_id <= node_range[1]:
            return not (other_node_id >= node_range[0] and other_node_id <= node_range[1])
        elif other_node_id >= node_range[0] and other_node_id <= node_range[1]:
            return not (node_id >= node_range[0] and node_id <= node_range[1])
    return False

def main():
    node_map_id = str(continent)
    node_lines = []
    node_zones = {}
    isolated_zones = [141, 1657]
    node_vertices = {}

    if continent < 2:
        node_lines = read_lines_from_file("2023_04_04_00_creature_template_npcbot_wander_nodes.sql")
    else:
        if TRICKERER_SQL:
            node_lines = read_lines_from_file("trickerer_outland_northrend.sql")
        else:
            node_lines = read_lines_from_file("2023_06_09_00_creature_template_npcbot_wander_nodes.sql")

    for line in node_lines:
        if line and line[0] == '(':
            map_id = extract_index(line, ',', 2).strip()
            if map_id == node_map_id:
                node_id = int(line.split(',')[0][1:].strip())
                node_links = re.sub(":0", "", extract_index(line, '\'', 3))
                links = [int(link) for link in node_links.split()]
                node_vertices[node_id] = links
                zone_id = int(extract_index(line, ',', 3))
                node_zones[node_id] = zone_id

    g = Graph()
    for node_id, node_links in node_vertices.items():
        for link in node_links:
            g.addEdge(node_id, link)

    g.should_print = True
    if continent == ContinentID.EasternKingdoms:
        assert g.DFS_search(686, 913)
        assert g.DFS_search(748, 942)
        assert g.DFS_search(778, 2)
    elif continent == ContinentID.Kalimdor:
        assert g.DFS_search(1005, 1236)
        assert g.DFS_search(26, 2366)
        assert g.DFS_search(1271, 95)
    elif TRICKERER_SQL:
        if continent == ContinentID.Outland:
            assert g.DFS_search(2418, 2864)
            assert g.DFS_search(2889, 3096)
            assert g.DFS_search(3257, 3442)
        else:
            assert g.DFS_search(4010, 4556)
            assert g.DFS_search(4992, 4362)
            assert g.DFS_search(3779, 5038)
    else:
        if continent == ContinentID.Outland:
            assert g.DFS_search(2418, 2474)
            assert g.DFS_search(2418, 2450)
            assert g.DFS_search(2500, 2602)
        else:
            assert g.DFS_search(2802, 2900)
            assert g.DFS_search(3273, 3330)
            assert g.DFS_search(3353, 2708)

    node_count = len(node_vertices)
    print(f"\nLooping all nodes... Nodes: {node_count}")
    links_to_all = True
    break_when_no_link = False
    loop_counter = 0
    isolated_counter = 0
    g.should_print = False

    for node_id in node_vertices:
        for other_node_id in node_vertices:
            if TRICKERER_SQL:
                trying_to_reach_isolated = (node_zones[node_id] in isolated_zones or node_zones[other_node_id] in isolated_zones) and node_zones[node_id] != node_zones[other_node_id] or isIsolatedNodes(node_id, other_node_id)
            else:
                trying_to_reach_isolated = (node_zones[node_id] in isolated_zones or node_zones[other_node_id] in isolated_zones) and node_zones[node_id] != node_zones[other_node_id]

            if trying_to_reach_isolated:
                isolated_counter += 1
            elif node_id != other_node_id and not trying_to_reach_isolated:
                can_reach = g.DFS_search(node_id, other_node_id)
                loop_counter += 1
                if not can_reach:
                    print(f"CAN'T REACH: {other_node_id} (zone: {node_zones[other_node_id]}) FROM NODE: {node_id} (zone: {node_zones[node_id]})")
                    links_to_all = False
                    if break_when_no_link:
                        break
        if not links_to_all and break_when_no_link:
            break

    print(f"Done checking links... links_to_all: {links_to_all}. Nodes checked: {loop_counter + isolated_counter} - should be {node_count} * {node_count - 1} = {node_count * (node_count - 1)}")
    print(f"isolated_counter: {isolated_counter} ({(isolated_counter / loop_counter) * 100} %)")

if __name__ == "__main__":
    main()