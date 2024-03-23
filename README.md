# ba

byte array implementation in c, basically its just convenience wrappers over
uint8\_t with hex string parsing and other common operations

# DO NOT USE FREE() ON BA POINTERS, USE BA\_FREE() OTHERWISE YOU LEAK MEM
