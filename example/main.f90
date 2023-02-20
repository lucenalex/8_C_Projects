PROGRAM example
    IMPLICIT NONE
    ! Declara��o explicita de vari�veis
    INTEGER, PARAMETER :: dois = 2  ! Constante nomeada
    INTEGER :: v2 = dois            ! Vari�vel inicializada
    INTEGER :: x                    ! Vari�vel n�o inicializada
    REAL :: a, b = 10.5e-2          ! b � inicializada a 10.5e-2.
    REAL, PARAMETER :: pi = 3.141593! Constante pi (aproximada)
    COMPLEX :: z = (5,-5), u, v     ! z � inicializada com o par (5,-5)
    COMPLEX, PARAMETER :: w = (6.0,-6.0)
    CHARACTER, PARAMETER :: c1 = 'v' ! Constante de CHARACTER de comprimento 1
    CHARACTER(len=*), PARAMETER :: tda= 'Tromba d"�gua' ! Comprimento assumido
    CHARACTER(len=10) :: str_read
    LOGICAL :: proposicao = .true.

    ! Vari�vel do tipo INTEGER
    PRINT *, "O valor da constante dois �: ", dois
    PRINT *, "Valor da vari�vel v2: ", v2
    ! O valor de a ser� agora lido do teclado
    PRINT *, "Valor de x: "
    READ *, x ! Entre um n�mero inteiro no cursor. O valor digitado n�o pode
    ! conter ponto (.). Caso isto aconte�a, pode ocorrer um erro de execu��o
    ! do programa, abortando o mesmo.
    PRINT*, "Valor lido: ",x

    ! Vari�vel do tipo REAL
    PRINT *, "Valor de a: "
    READ *, a
    PRINT *, "Valor de a: ", a
    PRINT *, "Valor de b: ", b
    PRINT *, "Valor de pi: ", pi

    ! Vari�vel do tipo COMPLEX
    PRINT *, "Valor de u"
    ! O valor de u deve ser entrado como um literal complexo
    ! Exemplo (-1.5,2.5)
    READ *, u
    v = z*u
    PRINT *, "O valor de v = z*u: ", v      ! Verifique o resultado no papel
    ! Acesso individual �s partes real ou imagin�ria:
    PRINT *, "Parte real: Re(v) = ", real(v)     ! Ou v%re (v.9 do Gfortran)
    PRINT *, "Parte imagin�ria: Im(v)", aimag(v) ! Ou v%im (v.9 do Gfortran)
    v = u/w
    PRINT *, "O valor de v=u/w: ", v ! Verifique o resultado no papel

    ! Vari�vel do tipo CHARACTER
    PRINT *, 'Imprimindo strings na tela: '
    PRINT *, 'As constantes est�o contidas entre os s�mbolos "->|" e "|<-".'
    PRINT *, 'Constante c1: ->|', c1, '|<-'
    PRINT *, 'Constante tda: ->|', tda, '|<-'
    PRINT *, "Entre com texto (sem aspas ou ap�strofes): "
    READ  '(a)' , str_read
    PRINT *, "Texto lido: ->|", str_read, "|<-"

    !Vari�vel do tipo LOGICAL
    IF (proposicao) THEN ! Bloco IF
        PRINT *, "A vari�vel � verdadeira."
    END IF
END PROGRAM example

