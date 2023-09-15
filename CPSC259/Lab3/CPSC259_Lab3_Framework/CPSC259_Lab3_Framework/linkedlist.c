/*
 File:         linkedlist.c
 Purpose:      Implements the linked list functions whose prototypes
               are declared in the linked_list.h header file
 Author:       Ruiqi Zang && Yifeng Liu
 Student #s:   24075277   && 28177384
 CWLs:         rzang01@student.ubc.ca
 Date:         19 Oct, 2022
 */

#define _CRT_SECURE_NO_WARNINGS

 /* Preprocessor directives */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/******************************************************************
 PLEASE EDIT THIS FILE

 Comments that start with // should be replaced with code
 Comments that are surrounded by * are hints
 ******************************************************************/

 /*
  Returns a pointer to a new, empty linked list of struct node.
  PRE:       NULL (no pre-conditions)
  POST:      NULL (no side-effects)
  RETURN:    A pointer to a new, empty linked list of struct node (NULL)
  */
node* create_linked_list()
{
  // Insert your code here
    node* node = NULL;
    return node;
}

/*
 Returns a dynamically allocated struct node that contains the specified
 struct airplane. Note that the string attributes of the newly created
 node's struct airplane must be specially copied (refer to lab 2).
 The node's next pointer doesn't point to anything
 PARAM:     plane, a struct airplane
 PRE:       NULL (no pre-conditions)
 POST:      NULL (no side-effects)
 RETURN:    A pointer to a dynamically allocated struct node a) that contains
            the specified struct airplane, and b) whose next pointer points to NULL
 */
node* create_node(airplane plane)
{
  // Insert your code here
    node* new_node;
     new_node = (node*) malloc(sizeof(node));
     new_node->plane.capacity = plane.capacity;
     new_node->plane.city_destination = (char*) malloc( (strlen(plane.city_destination)+1)*sizeof (char));
     strcpy(new_node->plane.city_destination, plane.city_destination);
     new_node->plane.city_origin = (char*)malloc((strlen(plane.city_origin) + 1) * sizeof(char));
     strcpy(new_node->plane.city_origin, plane.city_origin);
     new_node->plane.cruising_altitude = plane.cruising_altitude;
     new_node->plane.flight_number = plane.flight_number;
     new_node->plane.maximum_speed_kph = plane.maximum_speed_kph;
     new_node->plane.priority = plane.priority;
     new_node->next = NULL;
  // replace this line with something appropriate
  return new_node;
}

/*
 Prepends a struct node passed as a parameter to the list passed as a
 parameter, and returns a pointer to the result.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     new_node is a pointer to a struct node
 PRE:       new_mode is not null
 POST:      The specified struct node is added to the beginning of the list
            and its next pointer points to the node that used to be first
 RETURN:    A pointer to a linked list which contains all of the nodes
            of the list passed as a parameter, plus a prepended node
 */
node* prepend_node(node* list, node* new_node)
{
  new_node->next = list;   
  return new_node;
}

/*
 Deletes the first struct node in the specified list, and returns a pointer to
 the shortened list. Be aware of nested allocations!
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL
 POST:      The list passed as a parameter has one fewer node, and the dynamically
            allocated memory which contained that removed node has been freed
 RETURN:    IF the list is empty
            THEN NULL
            ELSE a pointer to the shortened list
 */
node* delete_node(node* list)
{
  // Insert your code here
   if (list == NULL) return NULL;
   else {
    node* delet = list->next;
    free(list->plane.city_destination);
    free(list->plane.city_origin);
    free(list);   
    return delet;
   }
    
  // replace this line with something appropriate
   
}

/*
 Returns the number of nodes in the specified linked list of struct node.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      NULL (no side-effects)
 RETURN:    The length of the specified list, an int
 */
int get_length(node* list)
{
  // Insert your code here
    int length = 0;
    while (list != NULL) {
        list = list->next;
        length++;
    }
  // replace this line with something appropriate
  return length;
}

/*
 Deletes an entire list.  This function iterates along a list and deallocates the
 memory containing each struct node.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      The memory containing all of the nodes in the list has been freed
 RETURN:    an empty list (NULL)
 */
node* delete_list(node* list)
{
  // Insert your code here
    node* curr = list;
    while(list != NULL) {
        list = list->next;
        free(curr->plane.city_destination);
        free(curr->plane.city_origin);
        free(curr);
        curr = list;
    }
    //list = NULL;
  // replace this line with something appropriate
  return list;
}

/*
 Prints the data stored in a node.  For the struct airplane in the node,
 prints the fields on separate lines.  For each field, prints the field name
 and the field value.  For the pointer, prints "Link = NULL\n" if the pointer points
 to null, else prints "Link points to address xxx\n", where xxx is the pointer address
 in hexademical.
 If node_to_print is NULL, prints "The node is empty\n".
 PARAM:     node_to_print is a pointer to a (possibly null) struct node
 PRE:       NULL (no pre-conditions)
 POST:      Information about node_to_print has been printed to standard output
 RETURN:    NULL
 */
void print_node(node* node_to_print)
{
  // Insert your code here
    if (node_to_print == NULL) {
        printf("The node is empty\n");
    }
    else {
        int i = 0;
        while (node_to_print) {
            printf("Link points to address %p\n", node_to_print);
            node_to_print = node_to_print->next;
            i++;
        }
        if (node_to_print == NULL) {
            printf("Link = NULL\n");
        }
    }

}

/*
 Prints the data stored in all nodes in the specified list to print.
 For each node, prints the data inside the node the same way that it
 is printed by print_node.  If the list is empty, a suitable message
 is printed to standard output.
 PARAM:     node_to_print is a pointer to a (possibly empty) linked list of
            struct node
 PRE:       NULL (no pre-conditions)
 POST:      Information about list_to_print has been printed to standard output
 RETURN:    NULL
 */
void print_list(node* list_to_print)
{
  // Insert your code here
    if (list_to_print == NULL) {
        printf("The list is empty\n");
    }
    else {
        while (list_to_print != NULL) {
            printf("Link lists to address %p\n", list_to_print);
            list_to_print = list_to_print->next;
        }
    }

}

/*
 Reverses a list.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      The order of the nodes in the list passed as a parameter has been
            reversed
 RETURN:    a list of struct node that is the reverse of the list passed as a
            parameter
 */
node* reverse(node* list)
{
  // Insert your code here
    node* prev = NULL;
    node* next = NULL;
    
    while (list != NULL) {
        next = list->next;
        list->next = prev;
        prev = list;
        list = next;
    }
    list = prev;


  // replace this line with something appropriate
  return list;
}

/*
 Removes every node from the list which contains an airplane destined for
 the city name passed in the second parameter.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     destination_city is a pointer to a null-terminated array of char
 PRE:       NULL (no pre-conditions)
 POST:      Any struct node in the list which contains an airplane struct
            destined for the destination_city is removed from the list, and
            the memory deallocated
 RETURN:    a list of struct node that does not contain any struct node that
            has an airplane destined for the destination_city
 */
node* remove_from_list(node* list, char* destination_city)
{
  // Insert your code here
    if (list == NULL) return NULL;

    if (strcmp(list->plane.city_destination, destination_city) == 0) {

        node* delet = list;
        list = list->next;
        free(delet->plane.city_destination);
        free(delet->plane.city_origin);
        free(delet);
    }
    else {    
        node* curr = list;
        //node* next_ptr = curr->next;
        while (curr != NULL && curr->next != NULL ) {
            if (strcmp(curr->next-> plane.city_destination, destination_city) == 0) {
                node* delet = curr->next;
                if (delet->next != NULL) {
                    delet = curr->next;
                    curr->next = delet->next;
                    free(delet->plane.city_destination);
                    free(delet->plane.city_origin);
                    free(delet);
                }
                else {
                    free(delet->plane.city_destination);
                    free(delet->plane.city_origin);
                    free(delet);
                    curr->next = NULL;
                }
                
            }
            curr = curr->next;
            //next_ptr = next_ptr->next; 
        }


    }
  // replace this line with something appropriate
  return list;
}

/*
 Returns a reference to the nth node (but does not remove it ) in the
 specified list.  If the list is too short, returns NULL.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     ordinality is an integer
 PRE:       ordinality > 0
 POST:      NULL (no side-effects)
 RETURN:    IF ordinality <= length of list
            THEN a pointer to the nth node
            ELSE NULL
 */
node* retrieve_nth(node* list, int ordinality)
{
  // Insert your code here
    int length = get_length(list);
    if (ordinality > length) return NULL;
    else {
        node* curr = list;
        for (int i = 1; i < ordinality; i++) {
            curr = curr->next;
        }
        //curr->next = NULL;
        return curr;
    }
  // replace this line with something appropriate
  
}

/*
 Inserts the specified node into the specified list of nodes at the specified
 ordinality.  For example, if ordinality = 1, this is a simple prepend_node
 operation.  If ordinality = 3, then when this function is finished, the third
 node in the list will be the node_to_insert.  If the ordinality = the length
 of the list + 1, then the node_to_insert is appended to the end of the list.
 If the ordinality > 1 + length of the list, the function returns a pointer
 to the unchanged list.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     ordinality is an integer
 PRE:       ordinality > 0
 PRE:       node_to_insert is NEVER a null (it is always a correct node pointer)
 POST:      NULL (no side-effects)
 RETURN:    IF ordinality <= length of list + 1
            THEN a pointer to the list which contains the node_to_insert in the
      correct location
            ELSE a pointer to the unchanged list
 */
node* insert_nth(node* list, node* node_to_insert, int ordinality)
{
  // Insert your code here
    if (list == NULL && ordinality==1) return node_to_insert;
    if (list == NULL) return NULL;


    int length = get_length(list);
    if (ordinality == 1) {
        node_to_insert->next = list;
        list = node_to_insert;
    }
    else if (ordinality <= length) {
        node* curr = list;
        for (int i = 1; i < ordinality-1; i++) {
            curr = curr->next;
        }
        node_to_insert->next = curr->next;
        curr->next = node_to_insert;
    }
    else if (ordinality == length + 1) {
        node* curr = list;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        node_to_insert->next = NULL;
        curr->next = node_to_insert;

    }

        return list;


  // replace this line with something appropriate

}