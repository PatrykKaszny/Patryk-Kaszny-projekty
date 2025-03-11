.data
    max_val dq 255          ; Maksymalna warto�� piksela
    threshold dq 255        ; Pr�g solaryzacji


.code

; Funkcja solaryzacji dla kana�u czerwonego
SolarizationAsmRed proc
    xor rax, rax            ; Zeruj rax, u�ywany jako offset do danych obrazu 
    mov r13, r9             ; Za�aduj pr�g solaryzacji z R9 do rejestru r13

processLoopRed:
    cmp rax, rdx            ; Sprawd�, czy offset (rax) przekroczy� rozmiar obrazu (rdx)
    jge doneRed             ; Je�li tak, zako�cz p�tl� (wszystkie piksele przetworzone)

    ; Wczytaj warto�� kana�u czerwonego dla bie��cego piksela
    movzx r8, byte ptr [rcx + rax]    ; Za�aduj warto�� R (piksel r) do rejestru r8

    ; Sprawd�, czy warto�� R jest poni�ej progu solaryzacji
    cmp r8, r13
    jg solarizeRed          ; Je�li warto�� R < pr�g, wykonaj solaryzacj�

    ; Je�li warto�� jest powy�ej progu, nie zmieniaj warto�ci piksela
    jmp skipRed

solarizeRed:
    ; Za�aduj warto�� piksela do rejestru xmm0
    movzx r8, byte ptr [rcx + rax]  ; Za�aduj warto�� R dla bie��cego piksela
    movd xmm0, r8                      ; Za�aduj warto�� do xmm0 (xmm0 = R)

    ; Za�aduj warto�� 255 do xmm1
    movd xmm1, r8                      ; Za�aduj warto�� do xmm1
    pcmpeqb xmm1, xmm1                 ; Wype�nij xmm1 warto�ci� 0xFF (255)
    psubb xmm1, xmm0                   ; Odwr�� warto�� piksela: xmm1 = 255 - xmm0 (dla jednego piksela)

    ; Zapisz wynik (solaryzowany piksel) do pami�ci
    movd r12, xmm1                     ; Przenie� wynik z xmm1 do r12
    mov byte ptr [rcx + rax], r12b     ; Zapisz solaryzowany piksel do pami�ci

skipRed:
    add rax, 3            ; Przejd� do nast�pnego piksela (3 bajty na piksel)
    jmp processLoopRed     ; Wr�� do pocz�tku p�tli

doneRed:
    ret
SolarizationAsmRed endp

; Funkcja solaryzacji dla kana�u zielonego
SolarizationAsmGreen proc
    xor rax, rax            ; Zeruj rax, aby zacz�� od pocz�tku obrazu
    mov r13, r9             ; Za�aduj pr�g solaryzacji z R9 (czwarty argument)

processLoopGreen:
    cmp rax, rdx            ; Sprawd�, czy offset przekroczy� rozmiar obrazu
    jge doneGreen           ; Je�li tak, zako�cz p�tl�

    ; Wczytaj warto�� kana�u zielonego (G) dla bie��cego piksela
    movzx r8, byte ptr [rcx + rax + 1]  ; Za�aduj warto�� G (piksel g) do rejestru r8

    ; Sprawd�, czy warto�� G jest poni�ej progu solaryzacji
    cmp r8, r13
    jg solarizeGreen          ; Je�li G < pr�g, wykonaj solaryzacj�

    ; Je�li warto�� jest powy�ej progu, nie zmieniaj warto�ci piksela
    jmp skipGreen

solarizeGreen:
    ; Za�aduj warto�� piksela do rejestru xmm0
    movzx r8, byte ptr [rcx + rax + 1]  ; Za�aduj warto�� G dla bie��cego piksela
    movd xmm0, r8                      ; Za�aduj warto�� do xmm0 (xmm0 = G)

    ; Za�aduj warto�� 255 do xmm1
    movd xmm1, r8                      ; Za�aduj warto�� do xmm1
    pcmpeqb xmm1, xmm1                 ; Wype�nij xmm1 warto�ci� 0xFF (255)
    psubb xmm1, xmm0                   ; Odwr�� warto�� piksela: xmm1 = 255 - xmm0 (dla jednego piksela)

    ; Zapisz wynik (solaryzowany piksel) do pami�ci
    movd r12, xmm1                     ; Przenie� wynik z xmm1 do r12
    mov byte ptr [rcx + rax + 1], r12b  ; Zapisz solaryzowany piksel do pami�ci

skipGreen:
    add rax, 3            ; Przejd� do nast�pnego piksela (3 bajty na piksel)
    jmp processLoopGreen   ; Wr�� do pocz�tku p�tli

doneGreen:
    ret
SolarizationAsmGreen endp

; Funkcja solaryzacji dla kana�u niebieskiego
SolarizationAsmBlue proc
    xor rax, rax            ; Zeruj rax, aby zacz�� od pocz�tku obrazu
    mov r13, r9             ; Za�aduj pr�g solaryzacji z R9 (czwarty argument)

processLoopBlue:
    cmp rax, rdx            ; Sprawd�, czy offset przekroczy� rozmiar obrazu
    jge doneBlue            ; Je�li tak, zako�cz p�tl�

    ; Wczytaj warto�� kana�u niebieskiego (B) dla bie��cego piksela
    movzx r8, byte ptr [rcx + rax + 2]  ; Za�aduj warto�� B (piksel b) do rejestru r8

    ; Sprawd�, czy warto�� B jest poni�ej progu solaryzacji
    cmp r8, r13
    jg solarizeBlue         ; Je�li B < pr�g, wykonaj solaryzacj�

    ; Je�li warto�� jest powy�ej progu, nie zmieniaj warto�ci piksela
    jmp skipBlue

solarizeBlue:
    ; Za�aduj warto�� piksela do rejestru xmm0
    movzx r8, byte ptr [rcx + rax + 2]  ; Za�aduj warto�� B dla bie��cego piksela
    movd xmm0, r8                      ; Za�aduj warto�� do xmm0 (xmm0 = B)

    ; Za�aduj warto�� 255 do xmm1
    movd xmm1, r8                      ; Za�aduj warto�� do xmm1
    pcmpeqb xmm1, xmm1                 ; Wype�nij xmm1 warto�ci� 0xFF (255)
    psubb xmm1, xmm0                   ; Odwr�� warto�� piksela: xmm1 = 255 - xmm0 (dla jednego piksela)

    ; Zapisz wynik (solaryzowany piksel) do pami�ci
    movd r12, xmm1                     ; Przenie� wynik z xmm1 do r12
    mov byte ptr [rcx + rax + 2], r12b  ; Zapisz solaryzowany piksel do pami�ci

skipBlue:
    add rax, 3            ; Przejd� do nast�pnego piksela (3 bajty na piksel)
    jmp processLoopBlue    ; Wr�� do pocz�tku p�tli

doneBlue:
    ret
SolarizationAsmBlue endp

; Funkcja solaryzacji ca�ego obrazu (��czy wszystkie kana�y)
ApplySolarizationAsm proc
    ; rcx - wska�nik na dane obrazu (piksele)
    ; rdx - rozmiar danych (w bajtach)
    ; r8  - liczba w�tk�w (numThreads)
    ; r9  - pr�g solaryzacji (threshold)

    mov r10, rcx            ; Zachowaj oryginalny wska�nik na dane obrazu
    mov r11, rdx            ; Zachowaj oryginalny rozmiar danych obrazu
    mov r12, r8             ; Zachowaj liczb� w�tk�w
    xor rax, rax            ; Zeruj rax, aby zacz�� od pocz�tku obrazu

    ; Zastosowanie solaryzacji dla ka�dego kana�u (R, G, B)
    call SolarizationAsmRed  ; Wywo�aj funkcj� solaryzacji dla kana�u czerwonego
    call SolarizationAsmGreen ; Wywo�aj funkcj� solaryzacji dla kana�u zielonego
    call SolarizationAsmBlue  ; Wywo�aj funkcj� solaryzacji dla kana�u niebieskiego

    ret
ApplySolarizationAsm endp
END
