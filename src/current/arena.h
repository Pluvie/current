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
  int64 size;
  int64 pos;
  struct region* next;
};

struct arena {
  struct region* begin;
  struct region* end;
};

#define ARENA_REGION_MIN_SIZE (8 * 1024)

function(arena_calloc, void*) (struct arena*, int64, int64);
function(arena_destroy, void) (struct arena*);
function(arena_init, struct arena*) (int64);
function(arena_malloc, void*) (struct arena*, int64);
function(arena_realloc, void*) (struct arena*, void*, int64);
function(arena_region_next, struct region*) (struct arena*, int64);
function(arena_region_search, struct region*) (struct arena*, void*);
function(arena_prealloc, void*) (struct arena*, int64);
