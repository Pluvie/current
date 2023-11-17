uint32 string_generator (
    char* forge,
    uint32 size
)
{
  static uint32 length = 0;
  static char character = 'a';

  length++;
  if (length >= size)
    length = 1;

  memset(forge, '\0', size);
  for (int c = 0; c < length; c++) {
    forge[c] = character;
    character++;
    if (character > 'z')
      character = 'a';
  }

  return length;
}
