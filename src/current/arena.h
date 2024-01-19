/**
               ___      .______       _______ .__   __.      ___      
              /   \     |   _  \     |   ____||  \ |  |     /   \     
             /  ^  \    |  |_)  |    |  |__   |   \|  |    /  ^  \    
            /  /_\  \   |      /     |   __|  |  . `  |   /  /_\  \   
           /  _____  \  |  |\  \----.|  |____ |  |\   |  /  _____  \  
          /__/     \__\ | _| `._____||_______||__| \__| /__/     \__\ 
                                                                                      **/

struct region {
  byte* data;
  u64   capacity;
  u64   position;
  struct region* next;
};

struct arena {
  struct region* begin;
  struct region* end;
};

#define ARENA_REGION_MIN_CAPACITY (32 * 1024)

function(arena_calloc, void*) (struct arena*, u64, u64);
function(arena_destroy, void) (struct arena*);
function(arena_init, struct arena*) (u64);
function(arena_malloc, void*) (struct arena*, u64);
function(arena_realloc, void*) (struct arena*, void*, u64);
function(arena_region_next, struct region*) (struct arena*, u64);
function(arena_region_search, struct region*) (struct arena*, void*);
function(arena_prealloc, void*) (struct arena*, u64);