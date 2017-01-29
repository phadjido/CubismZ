!  @file   sdc_interface.F90
!  @author Sheng Di (disheng222@gmail.com)
!  @date   Aug., 2014
!  @ Mathematics and Computer Science (MCS)
!  @ Argonne National Laboratory, Lemont, USA.
!  @brief  The key Fortran binding file to connect C language and Fortran (Fortran part)


MODULE SZ
	use :: ISO_C_BINDING
	INTERFACE SZ_Compress
		MODULE PROCEDURE SZ_Compress_d1_Fortran_REAL_K4
		MODULE PROCEDURE SZ_Compress_d2_Fortran_REAL_K4
		MODULE PROCEDURE SZ_Compress_d3_Fortran_REAL_K4
		MODULE PROCEDURE SZ_Compress_d4_Fortran_REAL_K4
		MODULE PROCEDURE SZ_Compress_d5_Fortran_REAL_K4		
		MODULE PROCEDURE SZ_Compress_d1_Fortran_REAL_K4_ARGS
		MODULE PROCEDURE SZ_Compress_d2_Fortran_REAL_K4_ARGS
		MODULE PROCEDURE SZ_Compress_d3_Fortran_REAL_K4_ARGS
		MODULE PROCEDURE SZ_Compress_d4_Fortran_REAL_K4_ARGS
		MODULE PROCEDURE SZ_Compress_d5_Fortran_REAL_K4_ARGS
		MODULE PROCEDURE SZ_Compress_d1_Fortran_REAL_K8
		MODULE PROCEDURE SZ_Compress_d2_Fortran_REAL_K8
		MODULE PROCEDURE SZ_Compress_d3_Fortran_REAL_K8
		MODULE PROCEDURE SZ_Compress_d4_Fortran_REAL_K8
		MODULE PROCEDURE SZ_Compress_d5_Fortran_REAL_K8
		MODULE PROCEDURE SZ_Compress_d1_Fortran_REAL_K8_ARGS
		MODULE PROCEDURE SZ_Compress_d2_Fortran_REAL_K8_ARGS
		MODULE PROCEDURE SZ_Compress_d3_Fortran_REAL_K8_ARGS
		MODULE PROCEDURE SZ_Compress_d4_Fortran_REAL_K8_ARGS
		MODULE PROCEDURE SZ_Compress_d5_Fortran_REAL_K8_ARGS
		MODULE PROCEDURE SZ_Compress_d1_Fortran_REAL_K4_Rev
		MODULE PROCEDURE SZ_Compress_d2_Fortran_REAL_K4_Rev
		MODULE PROCEDURE SZ_Compress_d3_Fortran_REAL_K4_Rev
		MODULE PROCEDURE SZ_Compress_d4_Fortran_REAL_K4_Rev
		MODULE PROCEDURE SZ_Compress_d5_Fortran_REAL_K4_Rev	
		MODULE PROCEDURE SZ_Compress_d1_Fortran_REAL_K4_ARGS_Rev
		MODULE PROCEDURE SZ_Compress_d2_Fortran_REAL_K4_ARGS_Rev
		MODULE PROCEDURE SZ_Compress_d3_Fortran_REAL_K4_ARGS_Rev
		MODULE PROCEDURE SZ_Compress_d4_Fortran_REAL_K4_ARGS_Rev
		MODULE PROCEDURE SZ_Compress_d5_Fortran_REAL_K4_ARGS_Rev
		MODULE PROCEDURE SZ_Compress_d1_Fortran_REAL_K8_Rev
		MODULE PROCEDURE SZ_Compress_d2_Fortran_REAL_K8_Rev
		MODULE PROCEDURE SZ_Compress_d3_Fortran_REAL_K8_Rev
		MODULE PROCEDURE SZ_Compress_d4_Fortran_REAL_K8_Rev
		MODULE PROCEDURE SZ_Compress_d5_Fortran_REAL_K8_Rev
		MODULE PROCEDURE SZ_Compress_d1_Fortran_REAL_K8_ARGS_Rev
		MODULE PROCEDURE SZ_Compress_d2_Fortran_REAL_K8_ARGS_Rev
		MODULE PROCEDURE SZ_Compress_d3_Fortran_REAL_K8_ARGS_Rev
		MODULE PROCEDURE SZ_Compress_d4_Fortran_REAL_K8_ARGS_Rev
		MODULE PROCEDURE SZ_Compress_d5_Fortran_REAL_K8_ARGS_Rev
	END INTERFACE SZ_Compress

	INTERFACE SZ_Decompress
		MODULE PROCEDURE SZ_Decompress_d1_Fortran_REAL_K4
		MODULE PROCEDURE SZ_Decompress_d2_Fortran_REAL_K4
		MODULE PROCEDURE SZ_Decompress_d3_Fortran_REAL_K4
		MODULE PROCEDURE SZ_Decompress_d4_Fortran_REAL_K4
		MODULE PROCEDURE SZ_Decompress_d5_Fortran_REAL_K4
		MODULE PROCEDURE SZ_Decompress_d1_Fortran_REAL_K8
		MODULE PROCEDURE SZ_Decompress_d2_Fortran_REAL_K8
		MODULE PROCEDURE SZ_Decompress_d3_Fortran_REAL_K8
		MODULE PROCEDURE SZ_Decompress_d4_Fortran_REAL_K8
		MODULE PROCEDURE SZ_Decompress_d5_Fortran_REAL_K8
	END INTERFACE SZ_Decompress

	CONTAINS

!Init and Finalize

	SUBROUTINE SZ_Init(config_File,ierr)
		implicit none
		CHARACTER(len=32) :: config_File
		INTEGER :: l,ierr
		CALL SZ_Init_c(config_File,len(trim(config_File)),ierr)
	END SUBROUTINE SZ_Init
	
	SUBROUTINE SZ_Finalize()
		CALL SZ_Finalize_c()
	END SUBROUTINE SZ_Finalize

!Compress functions that extract the dimension sizes and call C translation interface (single-precision)

	SUBROUTINE SZ_Compress_d1_Fortran_REAL_K4(VAR, Bytes, OutSize)
		implicit none
		REAL(KIND=4), DIMENSION(:) :: VAR
		INTEGER(kind=4) :: OutSize, R1
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		CALL SZ_Compress_d1_Float(VAR, Bytes, OutSize, R1)
	END SUBROUTINE SZ_Compress_d1_Fortran_REAL_K4

	SUBROUTINE SZ_Compress_d1_Fortran_REAL_K4_ARGS(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=4), DIMENSION(:) :: VAR
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1
		REAL(kind=4) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		CALL SZ_Compress_d1_Float_Args(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1)
	END SUBROUTINE SZ_Compress_d1_Fortran_REAL_K4_ARGS

	SUBROUTINE SZ_Compress_d2_Fortran_REAL_K4(VAR, Bytes, OutSize)
		implicit none
		REAL(KIND=4), DIMENSION(:,:) :: VAR
		INTEGER(kind=4) :: OutSize, R1, R2
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		CALL SZ_Compress_d2_Float(VAR, Bytes, OutSize, R1, R2)
	END SUBROUTINE SZ_Compress_d2_Fortran_REAL_K4

	SUBROUTINE SZ_Compress_d2_Fortran_REAL_K4_ARGS(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=4), DIMENSION(:,:) :: VAR
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2
		REAL(kind=4) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		CALL SZ_Compress_d2_Float_Args(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2)
	END SUBROUTINE SZ_Compress_d2_Fortran_REAL_K4_ARGS

	SUBROUTINE SZ_Compress_d3_Fortran_REAL_K4(VAR, Bytes, OutSize)
		implicit none
		REAL(KIND=4), DIMENSION(:,:,:) :: VAR
		INTEGER(kind=4) :: OutSize, R1, R2, R3, R
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R = R1*R2*R3
		allocate(temp(8*R)) !allocate the largest possible memory
		
		CALL SZ_Compress_d3_Float(VAR, temp, OutSize, R1, R2, R3)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)	
	END SUBROUTINE SZ_Compress_d3_Fortran_REAL_K4

	SUBROUTINE SZ_Compress_d3_Fortran_REAL_K4_ARGS(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=4), DIMENSION(:,:,:) :: VAR
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2, R3, R
		REAL(kind=4) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R = R1*R2*R3
		allocate(temp(8*R)) !allocate the largest possible memory

		CALL SZ_Compress_d3_Float_Args(VAR, temp, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2, R3)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)

	END SUBROUTINE SZ_Compress_d3_Fortran_REAL_K4_ARGS

	SUBROUTINE SZ_Compress_d4_Fortran_REAL_K4(VAR, Bytes, OutSize)
		implicit none
		REAL(KIND=4), DIMENSION(:,:,:,:) :: VAR
		INTEGER(kind=4) :: OutSize, R1, R2, R3, R4, R
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)

		R = R1*R2*R3*R4
		allocate(temp(8*R)) !allocate the largest possible memory
		
		CALL SZ_Compress_d4_Float(VAR, temp, OutSize, R1, R2, R3, R4)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)	
	END SUBROUTINE SZ_Compress_d4_Fortran_REAL_K4

	SUBROUTINE SZ_Compress_d4_Fortran_REAL_K4_ARGS(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=4), DIMENSION(:,:,:,:) :: VAR
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2, R3, R4, R
		REAL(kind=4) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)
		R = R1*R2*R3*R4
		allocate(temp(8*R)) !allocate the largest possible memory

		CALL SZ_Compress_d4_Float_Args(VAR, temp, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2, R3, R4)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)

	END SUBROUTINE SZ_Compress_d4_Fortran_REAL_K4_ARGS

	SUBROUTINE SZ_Compress_d5_Fortran_REAL_K4(VAR, Bytes, OutSize)
		implicit none
		REAL(KIND=4), DIMENSION(:,:,:,:,:) :: VAR
		INTEGER(kind=4) :: OutSize, R1, R2, R3, R4, R5, R
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)
		R5 = SIZE(VAR,5)
		R = R1*R2*R3*R4*R5
		allocate(temp(8*R)) !allocate the largest possible memory
		
		CALL SZ_Compress_d5_Float(VAR, temp, OutSize, R1, R2, R3, R4, R5)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)	
	END SUBROUTINE SZ_Compress_d5_Fortran_REAL_K4

	SUBROUTINE SZ_Compress_d5_Fortran_REAL_K4_ARGS(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=4), DIMENSION(:,:,:,:,:) :: VAR
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2, R3, R4, R5, R
		REAL(kind=4) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)
		R5 = SIZE(VAR,5)
		R = R1*R2*R3*R4*R5
		allocate(temp(8*R)) !allocate the largest possible memory

		CALL SZ_Compress_d5_Float_Args(VAR, temp, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2, R3, R4, R5)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)

	END SUBROUTINE SZ_Compress_d5_Fortran_REAL_K4_ARGS

!Compress functions that extract the dimension sizes and call C translation interfaces （double-precision)

	SUBROUTINE SZ_Compress_d1_Fortran_REAL_K8(VAR, Bytes, OutSize)
		implicit none
		REAL(KIND=8), DIMENSION(:) :: VAR
		INTEGER(kind=4) :: OutSize, R1
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		CALL SZ_Compress_d1_Double(VAR, Bytes, OutSize, R1)
	END SUBROUTINE SZ_Compress_d1_Fortran_REAL_K8

	SUBROUTINE SZ_Compress_d1_Fortran_REAL_K8_ARGS(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=8), DIMENSION(:) :: VAR
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1
		REAL(kind=8) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		CALL SZ_Compress_d1_Double_Args(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1)
	END SUBROUTINE SZ_Compress_d1_Fortran_REAL_K8_ARGS

	SUBROUTINE SZ_Compress_d2_Fortran_REAL_K8(VAR, Bytes, OutSize)
		implicit none
		REAL(KIND=8), DIMENSION(:,:) :: VAR
		INTEGER(kind=4) :: OutSize, R1, R2
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		CALL SZ_Compress_d2_Double(VAR, Bytes, OutSize, R1, R2)
	END SUBROUTINE SZ_Compress_d2_Fortran_REAL_K8

	SUBROUTINE SZ_Compress_d2_Fortran_REAL_K8_ARGS(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=8), DIMENSION(:,:) :: VAR
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2
		REAL(kind=8) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		CALL SZ_Compress_d2_Double_Args(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2)
	END SUBROUTINE SZ_Compress_d2_Fortran_REAL_K8_ARGS

	SUBROUTINE SZ_Compress_d3_Fortran_REAL_K8(VAR, Bytes, OutSize)
		implicit none
		REAL(KIND=8), DIMENSION(:,:,:) :: VAR
		INTEGER(kind=4) :: OutSize, R1, R2, R3, R
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R = R1*R2*R3
		allocate(temp(8*R)) !allocate the largest possible memory
		
		CALL SZ_Compress_d3_Double(VAR, temp, OutSize, R1, R2, R3)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)	
	END SUBROUTINE SZ_Compress_d3_Fortran_REAL_K8

	SUBROUTINE SZ_Compress_d3_Fortran_REAL_K8_ARGS(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=8), DIMENSION(:,:,:) :: VAR
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2, R3, R
		REAL(kind=8) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R = R1*R2*R3
		allocate(temp(8*R)) !allocate the largest possible memory

		CALL SZ_Compress_d3_Double_Args(VAR, temp, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2, R3)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)

	END SUBROUTINE SZ_Compress_d3_Fortran_REAL_K8_ARGS

	SUBROUTINE SZ_Compress_d4_Fortran_REAL_K8(VAR, Bytes, OutSize)
		implicit none
		REAL(KIND=8), DIMENSION(:,:,:,:) :: VAR
		INTEGER(kind=4) :: OutSize, R1, R2, R3, R4, R
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)

		R = R1*R2*R3*R4
		allocate(temp(8*R)) !allocate the largest possible memory
		
		CALL SZ_Compress_d4_Double(VAR, temp, OutSize, R1, R2, R3, R4)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)	
	END SUBROUTINE SZ_Compress_d4_Fortran_REAL_K8

	SUBROUTINE SZ_Compress_d4_Fortran_REAL_K8_ARGS(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=8), DIMENSION(:,:,:,:) :: VAR
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2, R3, R4, R
		REAL(kind=8) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)
		R = R1*R2*R3*R4
		allocate(temp(8*R)) !allocate the largest possible memory

		CALL SZ_Compress_d4_Double_Args(VAR, temp, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2, R3, R4)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)

	END SUBROUTINE SZ_Compress_d4_Fortran_REAL_K8_ARGS

	SUBROUTINE SZ_Compress_d5_Fortran_REAL_K8(VAR, Bytes, OutSize)
		implicit none
		REAL(KIND=8), DIMENSION(:,:,:,:,:) :: VAR
		INTEGER(kind=4) :: OutSize, R1, R2, R3, R4, R5, R
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)
		R5 = SIZE(VAR,5)
		R = R1*R2*R3*R4*R5
		allocate(temp(8*R)) !allocate the largest possible memory
		
		CALL SZ_Compress_d5_Double(VAR, temp, OutSize, R1, R2, R3, R4, R5)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)	
	END SUBROUTINE SZ_Compress_d5_Fortran_REAL_K8

	SUBROUTINE SZ_Compress_d5_Fortran_REAL_K8_ARGS(VAR, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=8), DIMENSION(:,:,:,:,:) :: VAR
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2, R3, R4, R5, R
                REAL(kind=8) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)
		R5 = SIZE(VAR,5)
		R = R1*R2*R3*R4*R5
		allocate(temp(8*R)) !allocate the largest possible memory

		CALL SZ_Compress_d5_Double_Args(VAR, temp, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2, R3, R4, R5)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)

	END SUBROUTINE SZ_Compress_d5_Fortran_REAL_K8_ARGS

!Comrpession functions with reserved value

	SUBROUTINE SZ_Compress_d1_Fortran_REAL_K4_Rev(VAR, ReValue, Bytes, OutSize)
		implicit none
		REAL(KIND=4), DIMENSION(:) :: VAR
		REAL(KIND=4) :: ReValue
		INTEGER(kind=4) :: OutSize, R1
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		CALL SZ_Compress_d1_Float_Rev(VAR, ReValue, Bytes, OutSize, R1)
	END SUBROUTINE SZ_Compress_d1_Fortran_REAL_K4_Rev

	SUBROUTINE SZ_Compress_d1_Fortran_REAL_K4_ARGS_Rev(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=4), DIMENSION(:) :: VAR
		REAL(KIND=4) :: ReValue
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1
		REAL(kind=4) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		CALL SZ_Compress_d1_Float_Rev_Args(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1)
	END SUBROUTINE SZ_Compress_d1_Fortran_REAL_K4_ARGS_Rev

	SUBROUTINE SZ_Compress_d2_Fortran_REAL_K4_Rev(VAR, ReValue, Bytes, OutSize)
		implicit none
		REAL(KIND=4), DIMENSION(:,:) :: VAR
		REAL(KIND=4) :: ReValue
		INTEGER(kind=4) :: OutSize, R1, R2
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		CALL SZ_Compress_d2_Float_Rev(VAR, ReValue, Bytes, OutSize, R1, R2)
	END SUBROUTINE SZ_Compress_d2_Fortran_REAL_K4_Rev

	SUBROUTINE SZ_Compress_d2_Fortran_REAL_K4_ARGS_Rev(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=4), DIMENSION(:,:) :: VAR
		REAL(KIND=4) :: ReValue
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2
		REAL(kind=4) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		CALL SZ_Compress_d2_Float_Rev_Args(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2)
	END SUBROUTINE SZ_Compress_d2_Fortran_REAL_K4_ARGS_Rev

	SUBROUTINE SZ_Compress_d3_Fortran_REAL_K4_Rev(VAR, ReValue, Bytes, OutSize)
		implicit none
		REAL(KIND=4), DIMENSION(:,:,:) :: VAR
		REAL(KIND=4) :: ReValue
		INTEGER(kind=4) :: OutSize, R1, R2, R3, R
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R = R1*R2*R3
		allocate(temp(8*R)) !allocate the largest possible memory
		
		CALL SZ_Compress_d3_Float_Rev(VAR, ReValue, temp, OutSize, R1, R2, R3)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)	
	END SUBROUTINE SZ_Compress_d3_Fortran_REAL_K4_Rev

	SUBROUTINE SZ_Compress_d3_Fortran_REAL_K4_ARGS_Rev(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=4), DIMENSION(:,:,:) :: VAR
		REAL(KIND=4) :: ReValue
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2, R3, R
		REAL(kind=4) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R = R1*R2*R3
		allocate(temp(8*R)) !allocate the largest possible memory

		CALL SZ_Compress_d3_Float_Rev_Args(VAR, ReValue, temp, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2, R3)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)

	END SUBROUTINE SZ_Compress_d3_Fortran_REAL_K4_ARGS_Rev

	SUBROUTINE SZ_Compress_d4_Fortran_REAL_K4_Rev(VAR, ReValue, Bytes, OutSize)
		implicit none
		REAL(KIND=4), DIMENSION(:,:,:,:) :: VAR
		REAL(KIND=4) :: ReValue
		INTEGER(kind=4) :: OutSize, R1, R2, R3, R4, R
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)

		R = R1*R2*R3*R4
		allocate(temp(8*R)) !allocate the largest possible memory
		
		CALL SZ_Compress_d4_Float_Rev(VAR, ReValue, temp, OutSize, R1, R2, R3, R4)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)	
	END SUBROUTINE SZ_Compress_d4_Fortran_REAL_K4_Rev

	SUBROUTINE SZ_Compress_d4_Fortran_REAL_K4_ARGS_Rev(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=4), DIMENSION(:,:,:,:) :: VAR
		REAL(KIND=4) :: ReValue
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2, R3, R4, R
		REAL(kind=4) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)
		R = R1*R2*R3*R4
		allocate(temp(8*R)) !allocate the largest possible memory

		CALL SZ_Compress_d4_Float_Rev_Args(VAR, ReValue, temp, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2, R3, R4)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)

	END SUBROUTINE SZ_Compress_d4_Fortran_REAL_K4_ARGS_Rev

	SUBROUTINE SZ_Compress_d5_Fortran_REAL_K4_Rev(VAR, ReValue, Bytes, OutSize)
		implicit none
		REAL(KIND=4), DIMENSION(:,:,:,:,:) :: VAR
		REAL(KIND=4) :: ReValue
		INTEGER(kind=4) :: OutSize, R1, R2, R3, R4, R5, R
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)
		R5 = SIZE(VAR,5)
		R = R1*R2*R3*R4*R5
		allocate(temp(8*R)) !allocate the largest possible memory
		
		CALL SZ_Compress_d5_Float_Rev(VAR, ReValue, temp, OutSize, R1, R2, R3, R4, R5)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)	
	END SUBROUTINE SZ_Compress_d5_Fortran_REAL_K4_Rev

	SUBROUTINE SZ_Compress_d5_Fortran_REAL_K4_ARGS_Rev(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=4), DIMENSION(:,:,:,:,:) :: VAR
		REAL(KIND=4) :: ReValue
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2, R3, R4, R5, R
		REAL(kind=4) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)
		R5 = SIZE(VAR,5)
		R = R1*R2*R3*R4*R5
		allocate(temp(8*R)) !allocate the largest possible memory

		CALL SZ_Compress_d5_Float_Rev_Args(VAR, ReValue, temp, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2, R3, R4, R5)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)

	END SUBROUTINE SZ_Compress_d5_Fortran_REAL_K4_ARGS_Rev

!Compress functions that extract the dimension sizes and call C translation interfaces （double-precision)

	SUBROUTINE SZ_Compress_d1_Fortran_REAL_K8_Rev(VAR, ReValue, Bytes, OutSize)
		implicit none
		REAL(KIND=8), DIMENSION(:) :: VAR
		REAL(KIND=8) :: ReValue
		INTEGER(kind=4) :: OutSize, R1
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		CALL SZ_Compress_d1_Double_Rev(VAR, ReValue, Bytes, OutSize, R1)
	END SUBROUTINE SZ_Compress_d1_Fortran_REAL_K8_Rev

	SUBROUTINE SZ_Compress_d1_Fortran_REAL_K8_ARGS_Rev(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=8), DIMENSION(:) :: VAR
		REAL(KIND=8) :: ReValue
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1
		REAL(kind=8) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		CALL SZ_Compress_d1_Double_Rev_Args(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1)
	END SUBROUTINE SZ_Compress_d1_Fortran_REAL_K8_ARGS_Rev

	SUBROUTINE SZ_Compress_d2_Fortran_REAL_K8_Rev(VAR, ReValue, Bytes, OutSize)
		implicit none
		REAL(KIND=8), DIMENSION(:,:) :: VAR
		REAL(KIND=8) :: ReValue
		INTEGER(kind=4) :: OutSize, R1, R2
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		CALL SZ_Compress_d2_Double_Rev(VAR, ReValue, Bytes, OutSize, R1, R2)
	END SUBROUTINE SZ_Compress_d2_Fortran_REAL_K8_Rev

	SUBROUTINE SZ_Compress_d2_Fortran_REAL_K8_ARGS_Rev(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=8), DIMENSION(:,:) :: VAR
		REAL(KIND=8) :: ReValue
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2
		REAL(kind=8) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		CALL SZ_Compress_d2_Double_Rev_Args(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2)
	END SUBROUTINE SZ_Compress_d2_Fortran_REAL_K8_ARGS_Rev

	SUBROUTINE SZ_Compress_d3_Fortran_REAL_K8_Rev(VAR, ReValue, Bytes, OutSize)
		implicit none
		REAL(KIND=8), DIMENSION(:,:,:) :: VAR
		REAL(KIND=8) :: ReValue
		INTEGER(kind=4) :: OutSize, R1, R2, R3, R
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R = R1*R2*R3
		allocate(temp(8*R)) !allocate the largest possible memory
		
		CALL SZ_Compress_d3_Double_Rev(VAR, ReValue, temp, OutSize, R1, R2, R3)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)	
	END SUBROUTINE SZ_Compress_d3_Fortran_REAL_K8_Rev

	SUBROUTINE SZ_Compress_d3_Fortran_REAL_K8_ARGS_Rev(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=8), DIMENSION(:,:,:) :: VAR
		REAL(KIND=8) :: ReValue
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2, R3, R
		REAL(kind=8) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R = R1*R2*R3
		allocate(temp(8*R)) !allocate the largest possible memory

		CALL SZ_Compress_d3_Double_Rev_Args(VAR, ReValue, temp, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2, R3)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)

	END SUBROUTINE SZ_Compress_d3_Fortran_REAL_K8_ARGS_Rev

	SUBROUTINE SZ_Compress_d4_Fortran_REAL_K8_Rev(VAR, ReValue, Bytes, OutSize)
		implicit none
		REAL(KIND=8), DIMENSION(:,:,:,:) :: VAR
		REAL(KIND=8) :: ReValue
		INTEGER(kind=4) :: OutSize, R1, R2, R3, R4, R
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)

		R = R1*R2*R3*R4
		allocate(temp(8*R)) !allocate the largest possible memory
		
		CALL SZ_Compress_d4_Double_Rev(VAR, ReValue, temp, OutSize, R1, R2, R3, R4)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)	
	END SUBROUTINE SZ_Compress_d4_Fortran_REAL_K8_Rev

	SUBROUTINE SZ_Compress_d4_Fortran_REAL_K8_ARGS_Rev(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=8), DIMENSION(:,:,:,:) :: VAR
		REAL(KIND=8) :: ReValue
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2, R3, R4, R
		REAL(kind=8) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)
		R = R1*R2*R3*R4
		allocate(temp(8*R)) !allocate the largest possible memory

		CALL SZ_Compress_d4_Double_Rev_Args(VAR, ReValue, temp, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2, R3, R4)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)

	END SUBROUTINE SZ_Compress_d4_Fortran_REAL_K8_ARGS_Rev

	SUBROUTINE SZ_Compress_d5_Fortran_REAL_K8_Rev(VAR, ReValue, Bytes, OutSize)
		implicit none
		REAL(KIND=8), DIMENSION(:,:,:,:,:) :: VAR
		REAL(KIND=8) :: ReValue
		INTEGER(kind=4) :: OutSize, R1, R2, R3, R4, R5, R
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)
		R5 = SIZE(VAR,5)
		R = R1*R2*R3*R4*R5
		allocate(temp(8*R)) !allocate the largest possible memory
		
		CALL SZ_Compress_d5_Double_Rev(VAR, ReValue, temp, OutSize, R1, R2, R3, R4, R5)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)	
	END SUBROUTINE SZ_Compress_d5_Fortran_REAL_K8_Rev

	SUBROUTINE SZ_Compress_d5_Fortran_REAL_K8_ARGS_Rev(VAR, ReValue, Bytes, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio)
		implicit none
		REAL(KIND=8), DIMENSION(:,:,:,:,:) :: VAR
		REAL(KIND=8) :: ReValue
		INTEGER(kind=4) :: OutSize, ErrBoundMode, R1, R2, R3, R4, R5, R
                REAL(kind=8) :: AbsErrBound, RelBoundRatio
		INTEGER(kind=1), DIMENSION(:), allocatable :: Bytes
		INTEGER(kind=1), DIMENSION(:), allocatable :: temp
		INTEGER(kind=4) :: COUNTER

		R1 = SIZE(VAR,1)
		R2 = SIZE(VAR,2)
		R3 = SIZE(VAR,3)
		R4 = SIZE(VAR,4)
		R5 = SIZE(VAR,5)
		R = R1*R2*R3*R4*R5
		allocate(temp(8*R)) !allocate the largest possible memory

		CALL SZ_Compress_d5_Double_Rev_Args(VAR, ReValue, temp, OutSize, ErrBoundMode, AbsErrBound, RelBoundRatio, R1, R2, R3, R4, R5)
		allocate(Bytes(OutSize))
		!copy temp to Bytes		
		do COUNTER=1, OutSize, 1
			Bytes(COUNTER) = temp(COUNTER)
		end do
		deallocate(temp)

	END SUBROUTINE SZ_Compress_d5_Fortran_REAL_K8_ARGS_Rev

!Decompress functions

	SUBROUTINE SZ_Decompress_d1_Fortran_REAL_K4(Bytes, VAR, R1) 
		implicit none
		INTEGER(kind=1), DIMENSION(:) :: Bytes
		REAL(KIND=4), DIMENSION(:), allocatable :: VAR
		INTEGER(kind=4) :: R1, BLength
		BLength = SIZE(Bytes)
		allocate(VAR(R1))
	
		CALL SZ_Decompress_d1_Float(Bytes, BLength, VAR, R1)
	END SUBROUTINE SZ_Decompress_d1_Fortran_REAL_K4

	SUBROUTINE SZ_Decompress_d2_Fortran_REAL_K4(Bytes, VAR, R1, R2) 
		implicit none
		INTEGER(kind=1), DIMENSION(:) :: Bytes	
		REAL(KIND=4), DIMENSION(:,:), allocatable :: VAR
		INTEGER(kind=4) :: R1, R2, BLength
		BLength = SIZE(Bytes)
		allocate(VAR(R1,R2))
	
		CALL SZ_Decompress_d2_Float(Bytes, BLength, VAR, R1, R2)
	END SUBROUTINE SZ_Decompress_d2_Fortran_REAL_K4

	SUBROUTINE SZ_Decompress_d3_Fortran_REAL_K4(Bytes, VAR, R1, R2, R3) 
		implicit none
		INTEGER(kind=1), DIMENSION(:) :: Bytes
		REAL(KIND=4), DIMENSION(:,:,:), allocatable :: VAR
		INTEGER(kind=4) :: R1, R2, R3, BLength
		BLength = SIZE(Bytes)
		allocate(VAR(R1,R2,R3))
	
		CALL SZ_Decompress_d3_Float(Bytes, BLength, VAR, R1, R2, R3)
	END SUBROUTINE SZ_Decompress_d3_Fortran_REAL_K4

	SUBROUTINE SZ_Decompress_d4_Fortran_REAL_K4(Bytes, VAR, R1, R2, R3, R4) 
		implicit none
		INTEGER(kind=1), DIMENSION(:) :: Bytes
		REAL(KIND=4), DIMENSION(:,:,:,:), allocatable :: VAR
		INTEGER(kind=4) :: R1, R2, R3, R4, BLength
		BLength = SIZE(Bytes)
		allocate(VAR(R1,R2,R3,R4))
	
		CALL SZ_Decompress_d4_Float(Bytes, BLength, VAR, R1, R2, R3, R4)
	END SUBROUTINE SZ_Decompress_d4_Fortran_REAL_K4

	SUBROUTINE SZ_Decompress_d5_Fortran_REAL_K4(Bytes, VAR, R1, R2, R3, R4, R5) 
		implicit none
		INTEGER(kind=1), DIMENSION(:) :: Bytes
		REAL(KIND=4), DIMENSION(:,:,:,:,:), allocatable :: VAR
		INTEGER(kind=4) :: R1, R2, R3, R4, R5, BLength
		BLength = SIZE(Bytes)
		allocate(VAR(R1,R2,R3,R4,R5))
	
		CALL SZ_Decompress_d5_Float(Bytes, BLength, VAR, R1, R2, R3, R4, R5)
	END SUBROUTINE SZ_Decompress_d5_Fortran_REAL_K4

	SUBROUTINE SZ_Decompress_d1_Fortran_REAL_K8(Bytes, VAR, R1) 
		implicit none
		INTEGER(kind=1), DIMENSION(:) :: Bytes
		REAL(KIND=8), DIMENSION(:), allocatable :: VAR
		INTEGER(kind=4) :: R1, BLength
		BLength = SIZE(Bytes)
		allocate(VAR(R1))
	
		CALL SZ_Decompress_d1_Double(Bytes, BLength, VAR, R1)
	END SUBROUTINE SZ_Decompress_d1_Fortran_REAL_K8

	SUBROUTINE SZ_Decompress_d2_Fortran_REAL_K8(Bytes, VAR, R1, R2) 
		implicit none
		INTEGER(kind=1), DIMENSION(:) :: Bytes
		REAL(KIND=8), DIMENSION(:,:), allocatable :: VAR
		INTEGER(kind=4) :: R1, R2, BLength
		BLength = SIZE(Bytes)
		allocate(VAR(R1,R2))
	
		CALL SZ_Decompress_d2_Double(Bytes, BLength, VAR, R1, R2)
	END SUBROUTINE SZ_Decompress_d2_Fortran_REAL_K8

	SUBROUTINE SZ_Decompress_d3_Fortran_REAL_K8(Bytes, VAR, R1, R2, R3) 
		implicit none
		INTEGER(kind=1), DIMENSION(:) :: Bytes
		REAL(KIND=8), DIMENSION(:,:,:), allocatable :: VAR
		INTEGER(kind=4) :: R1, R2, R3, BLength
		BLength = SIZE(Bytes)
		allocate(VAR(R1,R2,R3))
	
		CALL SZ_Decompress_d3_Double(Bytes, BLength, VAR, R1, R2, R3)
	END SUBROUTINE SZ_Decompress_d3_Fortran_REAL_K8

	SUBROUTINE SZ_Decompress_d4_Fortran_REAL_K8(Bytes, VAR, R1, R2, R3, R4) 
		implicit none
		INTEGER(kind=1), DIMENSION(:) :: Bytes
		REAL(KIND=8), DIMENSION(:,:,:,:), allocatable :: VAR
		INTEGER(kind=4) :: R1, R2, R3, R4, BLength
		BLength = SIZE(Bytes)
		allocate(VAR(R1,R2,R3,R4))
	
		CALL SZ_Decompress_d4_Double(Bytes, BLength, VAR, R1, R2, R3, R4)
	END SUBROUTINE SZ_Decompress_d4_Fortran_REAL_K8

	SUBROUTINE SZ_Decompress_d5_Fortran_REAL_K8(Bytes, VAR, R1, R2, R3, R4, R5) 
		implicit none
		INTEGER(kind=1), DIMENSION(:) :: Bytes
		REAL(KIND=8), DIMENSION(:,:,:,:,:), allocatable :: VAR
		INTEGER(kind=4) :: R1, R2, R3, R4, R5, BLength
		BLength = SIZE(Bytes, 1)
		allocate(VAR(R1,R2,R3,R4,R5))
	
		CALL SZ_Decompress_d5_Double(Bytes, BLength, VAR, R1, R2, R3, R4, R5)
	END SUBROUTINE SZ_Decompress_d5_Fortran_REAL_K8

END MODULE SZ
