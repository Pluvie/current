/**
 * Minimum map capacity. */
#define MAP_MIN_CAPACITY 8

/**
 * Defines the possible key statuses of the map. */
enum __map_key_status {
  __Map__Key_Status__Not_Used = 0,
  __Map__Key_Status__Used     = 1,
  __Map__Key_Status__Deleted  = 2,
};

/**
 * Defines the result output of the function #__map_find. */
enum __map_find_output {
  __Map_Find_Default  = 0,
  __Map_Find_Offset   = 1,
};

/**
 * Defines the operation mode of the function #__map_use. */
enum __map_use_opmode {
  __Map_Use_Default   = 0,
  __Map_Use_Rehashing = 1,
};
