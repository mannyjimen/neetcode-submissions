/*

two things we want to think:
- how are we storing key value pairs
- how do we keep track of usage order

sorted data structure that sorts by time, and is associated with a key value pair as well.
because we want access to the key value pairs in constant time, we need someway to store
the keyvalue pair into the key of the element in the data structure, as well as the time.
we store key value pairs in the keys of the elements in the data structure themselves,
and we can keep a hashmap that maps the key of the keypair to the key of the data structure element.
However, now thinking about it, if we call put (to update) the value of a key value pair, 
in order to get to the element that the key corresponds to (in order to update the key itself, which means erasing and reinserting),
we get a time complexity of O(logn) for a put operation.
Get operations CAN work in constant if we just grab the value from the hashmap's values. But this is not good enough.

Is there another data structure we can use that can get us to a certain element in O(1), while also keeping an order of elements and changing
whenever put and get gets called on one of these elements.

(dont know how to talk like i haven't seen this question before).

put [k,v]
[k,v]
put [k2,v2]
[k,v]->[k2,v2]
put [k3,v3]
[k, v]->[k2 v2]->[k3 v3]
put [k4, v4]
[k2,v2]->[k3, v3]->[k4, v4]
least                 most
get[k3]
[k2,v2]->[k3, v3]->[k4, v4] want to move k3 to the front,
connecting node before k3 to node ahead of h3, and then connected k3 ahead of the front node.
then, we can set the front node = k3

[k2,v2]->[k4, v4]->[k3, v3]
least               most
back                front

now what about actually getting a value from a key in O(1) or updating a value in O(1)?
If we want to check the entire list, front to back, thats O(n), way too slow.
Is there a way we can remember the Node* from the key itself? Yes, hashmap.
Map key -> Node*.
In this way, a call to get is simply going to hash the key to grab the Node* (O(1)), and then check the node's value (O(1)).
For a put operation, we can do the same, except instead of grabbing the value, we update it to something else.

Now, for both of these operations, the reassigments to front, and the prev and ahead of the node we are updating have to be done,
but this is a constant updating of pointers:
previous node next updated,
next node prev updated
front node next updated
current node next updated (set nptr).

4 reassignments (for now).

edge case
[k2,v2]->[k4, v4]->[k3, v3]

what if we call get(k2),
then we want to move k2's node to the front,
but [k2,v2] has no node behind it, therefore, we should not try to update
the "previous" nodes next, as it doesn't exist (nptr dereference).
The same can be said if we try to move a node in the front to the front (even though its already there),
we will try to access and update the node ahead of it and update its previous pointer.
HOWEVER, there is no node ahead of it, results in a nptr dereference.

We can set up dummy nodes that exist before and after the enitre list, so that the list now looks like
[dummy_back, 0] ->[k2,v2]->[k4, v4]->[k3, v3]->[dummy_front, 0]

This way, both those cases i just talked about don't result in a nptr dereference, as a prev node for the back node does exist, and a next node
for the front node exists as well (the dummy nodes).
The pointer reassigments should work correctly, because we treat these dummy nodes as real nodes.
(maybe talk about how the original reassignments might have to change now that we have dummy nodes).

for the actual reassignments and pointer movements.
we reassign the prev and ahead nodes of the current node we are updating first
and then we move the position of the current node to the front.

hashmap to remember node*
reassignments when calling put or get (list maintains recently used order)

eviction?
maintain current_capacity and capacity.
if current_capacity goes over
we need to do a "delete" to node that dummy back is pointing to.
remember dummby backs pointed node's next as new back node
remove dummy backs pointed node's pointers,
delete the dummy backs pointed node.
reassign dummy back to point to new back node, set new back node prev to dummy back.

*/

struct Node {
    int key;
    int val;

    Node* next;
    Node* prev;

    Node() {}
    Node(int key, int val): key{key}, val{val} {};
};

class LRUCache {
private:
    int capacity;
    int current_capacity;

    Node* front;
    Node* back;

    unordered_map<int, Node*> nodes;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->current_capacity = 0;
        
        this->front = new Node;
        this->back = new Node;

        front->prev = back;
        back->next = front;
    }
    
    void removeNode(Node* current) {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    void insertNode(Node* current) {
        front->prev->next = current;
        current->prev = front->prev;

        front->prev = current;
        current->next = front;
    }

    void moveToFront(Node* current) {
        removeNode(current);
        insertNode(current);
    }

    void evict() {
        Node* evicted = back->next;
        removeNode(evicted);

        evicted->prev = nullptr;
        evicted->next = nullptr;
        
        nodes.erase(evicted->key);
        delete evicted;

        current_capacity--;
    }

    int get(int key) {
        if (!nodes.contains(key)) {
            return -1;
        }    

        moveToFront(nodes[key]);

        return nodes[key]->val;
    }

    void put(int key, int value) {
        Node* current;

        if (!nodes.contains(key)) {
            current_capacity++;
            current = new Node(key, value);
            nodes[key] = current;

            insertNode(current);
        } else {
            current = nodes[key];
            current->val = value;
            moveToFront(current);
        }

        if (current_capacity > capacity) {
            evict();
        }
    }
};
