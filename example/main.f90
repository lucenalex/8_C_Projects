PROGRAM example
    IMPLICIT NONE
    ! Declaração explicita de variáveis
    INTEGER, PARAMETER :: dois = 2  ! Constante nomeada
    INTEGER :: v2 = dois            ! Variável inicializada
    INTEGER :: x                    ! Variável não inicializada
    REAL :: a, b = 10.5e-2          ! b é inicializada a 10.5e-2.
    REAL, PARAMETER :: pi = 3.141593! Constante pi (aproximada)
    COMPLEX :: z = (5,-5), u, v     ! z é inicializada com o par (5,-5)
    COMPLEX, PARAMETER :: w = (6.0,-6.0)
    CHARACTER, PARAMETER :: c1 = 'v' ! Constante de CHARACTER de comprimento 1
    CHARACTER(len=*), PARAMETER :: tda= 'Tromba d"água' ! Comprimento assumido
    CHARACTER(len=10) :: str_read
    LOGICAL :: proposicao = .true.

    ! Variável do tipo INTEGER
    PRINT *, "O valor da constante dois é: ", dois
    PRINT *, "Valor da variável v2: ", v2
    ! O valor de a será agora lido do teclado
    PRINT *, "Valor de x: "
    READ *, x ! Entre um número inteiro no cursor. O valor digitado não pode
    ! conter ponto (.). Caso isto aconteça, pode ocorrer um erro de execução
    ! do programa, abortando o mesmo.
    PRINT*, "Valor lido: ",x

    ! Variável do tipo REAL
    PRINT *, "Valor de a: "
    READ *, a
    PRINT *, "Valor de a: ", a
    PRINT *, "Valor de b: ", b
    PRINT *, "Valor de pi: ", pi

    ! Variável do tipo COMPLEX
    PRINT *, "Valor de u"
    ! O valor de u deve ser entrado como um literal complexo
    ! Exemplo (-1.5,2.5)
    READ *, u
    v = z*u
    PRINT *, "O valor de v = z*u: ", v      ! Verifique o resultado no papel
    ! Acesso individual às partes real ou imaginária:
    PRINT *, "Parte real: Re(v) = ", real(v)     ! Ou v%re (v.9 do Gfortran)
    PRINT *, "Parte imaginária: Im(v)", aimag(v) ! Ou v%im (v.9 do Gfortran)
    v = u/w
    PRINT *, "O valor de v=u/w: ", v ! Verifique o resultado no papel

    ! Variável do tipo CHARACTER
    PRINT *, 'Imprimindo strings na tela: '
    PRINT *, 'As constantes estão contidas entre os símbolos "->|" e "|<-".'
    PRINT *, 'Constante c1: ->|', c1, '|<-'
    PRINT *, 'Constante tda: ->|', tda, '|<-'
    PRINT *, "Entre com texto (sem aspas ou apóstrofes): "
    READ  '(a)' , str_read
    PRINT *, "Texto lido: ->|", str_read, "|<-"

    !Variável do tipo LOGICAL
    IF (proposicao) THEN ! Bloco IF
        PRINT *, "A variável é verdadeira."
    END IF
END PROGRAM example

