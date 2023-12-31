/**
 * Map function declarations. */

function(__map_calc_memsize, struct __map_memsize) (uint64, uint64, uint64);
function(__map_delete, bool) (struct __map_fp*, void*, uint64);
function(__map_find, int64) (struct __map_fp*, void*, uint64, enum __map_find_output);
function(__map_free, void) (struct __map_fp*);
function(__map_new, void*) (struct __map_config);
function(__map_rehash, void*) (void*, struct __map_fp*);
function(__map_use, int64) (struct __map_fp*, void*, uint64, enum __map_use_opmode);

function(__map_prebuilt_int32_compare, bool) (void*, void*);
function(__map_prebuilt_int32_hash, uint64) (void*);
function(__map_prebuilt_int32_print, void) (int32);
function(__map_prebuilt_int64_compare, bool) (void*, void*);
function(__map_prebuilt_int64_hash, uint64) (void*);
function(__map_prebuilt_int64_print, void) (int64);
function(__map_prebuilt_string_hash, uint64) (void*);
function(__map_prebuilt_string_print, void) (char*);
function(__map_prebuilt_string_compare, bool) (void*, void*);
function(__map_prebuilt_string_length, uint64) (void*);
