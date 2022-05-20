/*
Problem inf-I-05-0: asm-x86/basics-64
Реализуйте на языке ассемблера x86-64 функцию с сигнатурой:

extern int *A;

void very_important_function(size_t N);

      
Эта функция должна в цикле N раз:

вводит с клавиатуры знаковое целое 32-битное число;
умножает его на текущий элемент массива A;
выводит результат на экран.
*/

.data
scan_format:
    .string "%d"
print_format:
    .string "%lld\n"

.intel_syntax noprefix
.text
.global A
.global very_important_function

// Регистр rbp всегда имеет большее значение нежели rsp
// потому что стек всегда начинается со старшего адреса памяти и растет в сторону младших адресов.

very_important_function:
     // rbp - это указатель на верхнюю границу стека, пушим мы его ,что бы не испортить
     // Первые две инструкции называются прологом функции или преамбулой.
     // Первым делом записываем старый указатель базы в стек, чтобы      
     // сохранить его на будущее. Потом копируем значение указателя стека в указатель базы.
     // После этого rbp указывает на базовый сегмент стекового фрейма функции main.
	push rbp
	mov rbp, rsp
	
	// выделяем место на стеке rbp всегде больше rsp
	sub rsp, 32
	
	// rsp + 8 = N
	mov [rsp + 8], rdi
	
	// index of array = 0
	mov QWORD PTR [rsp + 16], 0
	jmp stop

start:
	lea rdi, [rip + scan_format]
	mov rsi, rsp
	call scanf
	// eax will be 1 if scanf successfully converted an arg 
	
	mov rax, A
	
	// Move doubleword to quadword with sign-extension.
	// Переместить двойное слово в четверное слово с расширением знака.
	mov rbx, [rsp + 16]
	mov rcx, [rax + rbx*4]
	movsxd rax, dword ptr [rsp]
	// умножение со знаком
	imul rcx
	
	mov rsi, rax
	lea rdi, [rip + print_format]
	call printf
	// eax will be 1 if scanf successfully converted an arg 
	
	add rbx, 1
	mov [rsp + 16], rbx

stop:
       // rbx = N = 0
	cmp rbx, [rsp + 8]
	jl start
	add rsp, 32
	mov rbp, rsp
	pop rbp
	ret
