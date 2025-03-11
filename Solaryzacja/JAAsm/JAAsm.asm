.data
    max_val dq 255          ; Maksymalna wartoœæ piksela
    threshold dq 255        ; Próg solaryzacji


.code

; Funkcja solaryzacji dla kana³u czerwonego
SolarizationAsmRed proc
    xor rax, rax            ; Zeruj rax, u¿ywany jako offset do danych obrazu 
    mov r13, r9             ; Za³aduj próg solaryzacji z R9 do rejestru r13

processLoopRed:
    cmp rax, rdx            ; SprawdŸ, czy offset (rax) przekroczy³ rozmiar obrazu (rdx)
    jge doneRed             ; Jeœli tak, zakoñcz pêtlê (wszystkie piksele przetworzone)

    ; Wczytaj wartoœæ kana³u czerwonego dla bie¿¹cego piksela
    movzx r8, byte ptr [rcx + rax]    ; Za³aduj wartoœæ R (piksel r) do rejestru r8

    ; SprawdŸ, czy wartoœæ R jest poni¿ej progu solaryzacji
    cmp r8, r13
    jg solarizeRed          ; Jeœli wartoœæ R < próg, wykonaj solaryzacjê

    ; Jeœli wartoœæ jest powy¿ej progu, nie zmieniaj wartoœci piksela
    jmp skipRed

solarizeRed:
    ; Za³aduj wartoœæ piksela do rejestru xmm0
    movzx r8, byte ptr [rcx + rax]  ; Za³aduj wartoœæ R dla bie¿¹cego piksela
    movd xmm0, r8                      ; Za³aduj wartoœæ do xmm0 (xmm0 = R)

    ; Za³aduj wartoœæ 255 do xmm1
    movd xmm1, r8                      ; Za³aduj wartoœæ do xmm1
    pcmpeqb xmm1, xmm1                 ; Wype³nij xmm1 wartoœci¹ 0xFF (255)
    psubb xmm1, xmm0                   ; Odwróæ wartoœæ piksela: xmm1 = 255 - xmm0 (dla jednego piksela)

    ; Zapisz wynik (solaryzowany piksel) do pamiêci
    movd r12, xmm1                     ; Przenieœ wynik z xmm1 do r12
    mov byte ptr [rcx + rax], r12b     ; Zapisz solaryzowany piksel do pamiêci

skipRed:
    add rax, 3            ; PrzejdŸ do nastêpnego piksela (3 bajty na piksel)
    jmp processLoopRed     ; Wróæ do pocz¹tku pêtli

doneRed:
    ret
SolarizationAsmRed endp

; Funkcja solaryzacji dla kana³u zielonego
SolarizationAsmGreen proc
    xor rax, rax            ; Zeruj rax, aby zacz¹æ od pocz¹tku obrazu
    mov r13, r9             ; Za³aduj próg solaryzacji z R9 (czwarty argument)

processLoopGreen:
    cmp rax, rdx            ; SprawdŸ, czy offset przekroczy³ rozmiar obrazu
    jge doneGreen           ; Jeœli tak, zakoñcz pêtlê

    ; Wczytaj wartoœæ kana³u zielonego (G) dla bie¿¹cego piksela
    movzx r8, byte ptr [rcx + rax + 1]  ; Za³aduj wartoœæ G (piksel g) do rejestru r8

    ; SprawdŸ, czy wartoœæ G jest poni¿ej progu solaryzacji
    cmp r8, r13
    jg solarizeGreen          ; Jeœli G < próg, wykonaj solaryzacjê

    ; Jeœli wartoœæ jest powy¿ej progu, nie zmieniaj wartoœci piksela
    jmp skipGreen

solarizeGreen:
    ; Za³aduj wartoœæ piksela do rejestru xmm0
    movzx r8, byte ptr [rcx + rax + 1]  ; Za³aduj wartoœæ G dla bie¿¹cego piksela
    movd xmm0, r8                      ; Za³aduj wartoœæ do xmm0 (xmm0 = G)

    ; Za³aduj wartoœæ 255 do xmm1
    movd xmm1, r8                      ; Za³aduj wartoœæ do xmm1
    pcmpeqb xmm1, xmm1                 ; Wype³nij xmm1 wartoœci¹ 0xFF (255)
    psubb xmm1, xmm0                   ; Odwróæ wartoœæ piksela: xmm1 = 255 - xmm0 (dla jednego piksela)

    ; Zapisz wynik (solaryzowany piksel) do pamiêci
    movd r12, xmm1                     ; Przenieœ wynik z xmm1 do r12
    mov byte ptr [rcx + rax + 1], r12b  ; Zapisz solaryzowany piksel do pamiêci

skipGreen:
    add rax, 3            ; PrzejdŸ do nastêpnego piksela (3 bajty na piksel)
    jmp processLoopGreen   ; Wróæ do pocz¹tku pêtli

doneGreen:
    ret
SolarizationAsmGreen endp

; Funkcja solaryzacji dla kana³u niebieskiego
SolarizationAsmBlue proc
    xor rax, rax            ; Zeruj rax, aby zacz¹æ od pocz¹tku obrazu
    mov r13, r9             ; Za³aduj próg solaryzacji z R9 (czwarty argument)

processLoopBlue:
    cmp rax, rdx            ; SprawdŸ, czy offset przekroczy³ rozmiar obrazu
    jge doneBlue            ; Jeœli tak, zakoñcz pêtlê

    ; Wczytaj wartoœæ kana³u niebieskiego (B) dla bie¿¹cego piksela
    movzx r8, byte ptr [rcx + rax + 2]  ; Za³aduj wartoœæ B (piksel b) do rejestru r8

    ; SprawdŸ, czy wartoœæ B jest poni¿ej progu solaryzacji
    cmp r8, r13
    jg solarizeBlue         ; Jeœli B < próg, wykonaj solaryzacjê

    ; Jeœli wartoœæ jest powy¿ej progu, nie zmieniaj wartoœci piksela
    jmp skipBlue

solarizeBlue:
    ; Za³aduj wartoœæ piksela do rejestru xmm0
    movzx r8, byte ptr [rcx + rax + 2]  ; Za³aduj wartoœæ B dla bie¿¹cego piksela
    movd xmm0, r8                      ; Za³aduj wartoœæ do xmm0 (xmm0 = B)

    ; Za³aduj wartoœæ 255 do xmm1
    movd xmm1, r8                      ; Za³aduj wartoœæ do xmm1
    pcmpeqb xmm1, xmm1                 ; Wype³nij xmm1 wartoœci¹ 0xFF (255)
    psubb xmm1, xmm0                   ; Odwróæ wartoœæ piksela: xmm1 = 255 - xmm0 (dla jednego piksela)

    ; Zapisz wynik (solaryzowany piksel) do pamiêci
    movd r12, xmm1                     ; Przenieœ wynik z xmm1 do r12
    mov byte ptr [rcx + rax + 2], r12b  ; Zapisz solaryzowany piksel do pamiêci

skipBlue:
    add rax, 3            ; PrzejdŸ do nastêpnego piksela (3 bajty na piksel)
    jmp processLoopBlue    ; Wróæ do pocz¹tku pêtli

doneBlue:
    ret
SolarizationAsmBlue endp

; Funkcja solaryzacji ca³ego obrazu (³¹czy wszystkie kana³y)
ApplySolarizationAsm proc
    ; rcx - wskaŸnik na dane obrazu (piksele)
    ; rdx - rozmiar danych (w bajtach)
    ; r8  - liczba w¹tków (numThreads)
    ; r9  - próg solaryzacji (threshold)

    mov r10, rcx            ; Zachowaj oryginalny wskaŸnik na dane obrazu
    mov r11, rdx            ; Zachowaj oryginalny rozmiar danych obrazu
    mov r12, r8             ; Zachowaj liczbê w¹tków
    xor rax, rax            ; Zeruj rax, aby zacz¹æ od pocz¹tku obrazu

    ; Zastosowanie solaryzacji dla ka¿dego kana³u (R, G, B)
    call SolarizationAsmRed  ; Wywo³aj funkcjê solaryzacji dla kana³u czerwonego
    call SolarizationAsmGreen ; Wywo³aj funkcjê solaryzacji dla kana³u zielonego
    call SolarizationAsmBlue  ; Wywo³aj funkcjê solaryzacji dla kana³u niebieskiego

    ret
ApplySolarizationAsm endp
END
