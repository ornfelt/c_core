# https://leetcode.com/problems/defanging-an-ip-address/solutions/328895/java-python-3-3-one-liners-one-w-o-lib-w-analysis/?orderBy=most_votes

# All characters are visited at most twice, therefore,

# Time & space: O(n), where n = address.length().

def defangIPaddr(self, address: str) -> str:
    return address.replace('.', '[.]')
    
def defangIPaddrV2(self, address: str) -> str:
    return '[.]'.join(address.split('.'))
    
def defangIPaddrV3(self, address: str) -> str:
    return re.sub('\.', '[.]', address)
    
def defangIPaddrV4(self, address: str) -> str:
    return ''.join('[.]' if c == '.' else c for c in address)

""" 
JAVA:

public String defangIPaddr(String address) {
    return address.replace(".", "[.]");
}
public String defangIPaddr(String address) {
    return String.join("[.]", address.split("\\."));
}
public String defangIPaddr(String address) {
    return address.replaceAll("\\.", "[.]");
}
public String defangIPaddr(String address) {
    StringBuilder sb = new StringBuilder();
    for (char c : address.toCharArray()) {
        sb.append(c == '.' ? "[.]" : c);
    }
    return sb.toString();
}
"""