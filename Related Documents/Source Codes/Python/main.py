import random
import sys
sys.setrecursionlimit(10**6)

class Node:
    def __init__(self, key):
        self.key = key
        self.prior = random.randint(1,10**9)
        self.l = None
        self.r = None

class HeapTree:
    def __init__(self):
        self.root = None

    def split(self, t, key):
        if t is None:
            return None, None
        if t.key <= key:
            l1, r = self.split(t.r, key)
            t.r = l1
            return t, r
        else:
            l, r1 = self.split(t.l, key)
            t.l = r1
            return l, t
        
    def merge(self, l, r):
        if l is None:
            return r
        if r is None:
            return l
        if l.prior > r.prior:
            l.r = self.merge(l.r, r)
            return l
        else:
            r.l = self.merge(l, r.l)
            return r
        
    def find(self, t, key):
        if t is None:
            return 0
        if t.key == key:
            return 1
        if key < t.key:
            return self.find(t.l, key)
        else:
            return self.find(t.r, key)

    def insert(self, key):
        if self.find(self.root, key):
            return
        l, r = self.split(self.root, key)
        node = Node(key)
        self.root = self.merge(self.merge(l, node), r)

    def erase(self, key):
        l, r = self.split(self.root, key)
        l, mid = self.split(l, key-1)
        self.root = self.merge(l, r)

myTree = HeapTree()
q = int(input())

for i in range(q):
    s, val = input().split()
    val = int(val)

    if s == "Find":
        if myTree.find(myTree.root, val):
            print("Exist")
        else:
            print("Non-exist")
    elif s == "Insert":
        myTree.insert(val)
    elif s == "Erase":
        myTree.erase(val)



