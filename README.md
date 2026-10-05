# Circular-Linked-List-Monopoly
## How to Use
Upload all files into an IDE. Interact with the game by using the text input.

## Explanation (Circular Linked List):
  ### Appending: 
  Checks to see if the linked list is empty. If it is empty, it appoints the node as the head, and makes its pointer point to itself. Otherwise, it creates a temporary node and traverses the list starting from the head. The temporary node compares the next node with the head node in order to find the tail. Once the tail is found, the tail’s pointer points to the node and then the new node’s pointer points to the head. Because it traverses throughout the whole node, it has time complexity O(n). Space complexity is O(1) since only 2 nodes are created.
  ### Searching:
  We iterate through the list starting from the head, and compare each node’s property name to the desired property name until we find a match. We return the node with a matching name. Otherwise, we return a null pointer. Time complexity is O(n) and space complexity is O(1). 
  ### Removing:
  Locates the desired node by searching for the name of the property. There are three possible events. (1) There are zero nodes in the linked list. We simply report that there is no node to possibly remove. (2) The desired node is at the head. In this case, we delete the head and then fix the list by appointing a new head and fixing the tail’s pointer. (3) The desired node is in the body. Here, we just traverse through the list until we find what we want and then fix the pointers. If there are no nodes matching the description, then we report that there is no node. Since fixing the pointers takes a fixed amount of time, and we also traverse through the whole list in its worst case, removing has a time complexity of O(n).  
  ### Printing:
  We just print out all the data in a node. If we want to print the entire linked list, then we just run the printing command while iterating through the list. O(1) time complexity for a single node. O(n) time complexity for the whole list. O(1) space complexity regardless

## Personal Grievances
First time I ever coded something this big :D
It was awful. I feel like I should have organized my code in a much more intuitive way. At first I tried using classes and structures to neatly group things together, but then that made it hard for me to properly make two objects interact with each other :/
I spent more time trying to understand the functions than organizing it. Maybe I should learn a little bit more about object oriented programming.
