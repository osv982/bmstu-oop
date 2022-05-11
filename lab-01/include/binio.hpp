#ifndef BINIO_HPP
#define BINIO_HPP

#define read(value, file) fread (&(value), sizeof(value), 1, (file))
#define dump(value, file) fwrite(&(value), sizeof(value), 1, (file))

#endif // BINIO_HPP
