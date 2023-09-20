#include "main.h"

/**
 * _printf - Custom printf function
 * @format: The format string.
 * Return: The number of characters printed (excluding the null byte).
 */
int _printf(const char *format, ...)
{
    int printed_chars = 0;
    int buffer_index = 0;
    va_list args;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(args, format);

    for (int i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buffer_index++] = format[i];
            if (buffer_index == BUFF_SIZE)
                print_buffer(buffer, &buffer_index);
            printed_chars++;
        }
        else
        {
            print_buffer(buffer, &buffer_index);
            i++;
            printed_chars += handle_format(format, &i, args, buffer);
            if (printed_chars == -1)
                return (-1);
        }
    }

    print_buffer(buffer, &buffer_index);

    va_end(args);

    return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of characters
 * @buff_index: Index to add the next character, represents the length.
 */
void print_buffer(char buffer[], int *buff_index)
{
    if (*buff_index > 0)
        write(1, &buffer[0], *buff_index);

    *buff_index = 0;
}

