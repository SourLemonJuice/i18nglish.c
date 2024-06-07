/* structures */
struct i7h_data_struct
{
    char *buffer;
    size_t buffer_size;
};

/* functions */
// main i7h processor
int i7h_processor(struct i7h_data_struct i7h_data[restrict], const char src_string[restrict]);
// free buffer(if have)
int i7h_reset_structure(struct i7h_data_struct i7h_data[restrict]);
