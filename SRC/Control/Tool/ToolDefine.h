
enum MOVE_STATUS
{
	NO_MOVING,
	SELECTTRAKER_DRAWING,
	ELEMENT_MOVING, 
	HANDLE_MOVING,
	VERTIX_MOVING
};

enum CAN_MOVE_CONTENT
{
	CMC_CANMOVE_NONE,
	CMC_CANMOVE_ELEMENT, 
	CMC_CANMOVE_HANDLE,
	CMC_CANMOVE_VERTIX
};