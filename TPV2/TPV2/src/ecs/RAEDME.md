# Entity-Component-System v3

This version implements Entity-Component-Systems. Components inherit from the struct Component, Entity maintains an array with a fixed number of (possible) components, and Manager maintains a list of entities. 


We still have update/render in Entity and Component just to allow using it without systems as well, they can be removed.

It also support groups of entities and handlers (assigning identifiers to entities for fast global access). Each entity belongs to a single group, resulting in a more efficient implementation. Entities keep no information on groups, everything is done in the manager.

It supports sending messages between systems.


