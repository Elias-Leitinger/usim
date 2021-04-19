/* create object type, which contains the infrmation for in game objects*/
typedef struct object object;
/* create type for moving things*/
typedef struct entity entity;
/* special attributes for object*/
/*TODO!*/


/*
id: unique object identifier, if 0, ignore object
type: object type, determines properties of object
user: entity who is using the object
content: content pointer points to contents of the object, use depends on object type. (Box content, Table top)
 */
struct object {
	int id;               
	int type;            
	entity *user;        
	object *content;     
};                           

struct entity {
	int id;
	int type;
	int x;
	int y;
	/* TODO! */
};
