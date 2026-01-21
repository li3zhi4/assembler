void _print_string_pm(int col, int row, char* s);
void _clear_screen_pm();

void main() {
    _clear_screen_pm();
    _print_string_pm(0, 0, "Kernel loaded successfully! We are now in 32-bit protected mode.");
    _print_string_pm(0, 1, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    _print_string_pm(0, 2, "abcdefghijklmnopqrstuvwxyz");
    _print_string_pm(0, 3, "0123456789");
    _print_string_pm(0, 4, "!@#$%^&*()_+-=[]{};':\",./<>?");
}
