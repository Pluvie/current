/**
               ___      .______       _______ .__   __.      ___      
              /   \     |   _  \     |   ____||  \ |  |     /   \     
             /  ^  \    |  |_)  |    |  |__   |   \|  |    /  ^  \    
            /  /_\  \   |      /     |   __|  |  . `  |   /  /_\  \   
           /  _____  \  |  |\  \----.|  |____ |  |\   |  /  _____  \  
          /__/     \__\ | _| `._____||_______||__| \__| /__/     \__\ 
                                                                                      **/

/**
 * # Arena
 *
 * An arena is a well-defined memory allocator.
 *
 * Arenas can be relied upon in order to help memory management in a program.
 * Allocations of memory blocks are performed using the arena reserved space, and their
 * release shall be done all at once by destroying the arena.
 *
 * This greatly helps in situation where memory can be seen as a whole, e.g. a web
 * request handler or a video game main loop frame: all resources needed are allocated
 * without worrying about having to release them singularly one by one.
 *
 * The arena memory space is organized in regions: see below.
 *
 * ## Region
 *
 * An arena region is a space in memory where the arena can perform its allocations.
 * Regions are stored as linked lists, where each region remembers their next one.
 *
 * Regions are fixed in size: when more memory is requested to the arena, and it doesn't
 * fit within the last region, a new one will be created and linked to the last. */


struct region;
typedef struct region {
  byte* data;
  u64   capacity;
  u64   position;
  struct region* next;
} Region;


struct arena;
typedef struct arena {
  u64 total_capacity;
  u64 number_of_allocs;
  u64 number_of_regions;
  Region* begin;
  Region* end;
} Arena;


/**
 * Initialization helper. */
#define arena_init() { 0 }


/**
 * All arena function definitions. */

void*     arena_create          ( Arena*, u64 );
void*     arena_calloc          ( Arena*, u64, u64 );
void      arena_destroy         ( Arena* );
void*     arena_malloc          ( Arena*, u64 );
void*     arena_prealloc        ( Arena*, u64 );
void*     arena_realloc         ( Arena*, void*, u64 );
Region*   arena_region_create   ( Arena*, u64 );
Region*   arena_region_next     ( Arena*, u64 );
Region*   arena_region_search   ( Arena*, void* );
