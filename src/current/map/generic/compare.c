bool map_generic_compare (
    void* key_1,
    void* key_2,
    size key_size
)
{
  for (size i = 0; i < key_size; i++)
    if (((byte*) key_1)[i] != ((byte*) key_2)[i])
      return false;

  return true;
}
