# UNIST 2-1 고급프로그래밍 과제 (Advanced Programming Assignments)

이 저장소는 UNIST 2-1 학기 고급프로그래밍 수업의 과제 구현 내용을 담고 있습니다. 각 과제는 독립된 폴더로 구성되어 있으며, 체계적인 관리를 위해 내부 구조가 분류되어 있습니다.

## 📂 폴더 구조 (Folder Structure)

각 과제 폴더(`AssignmentXX`)는 다음과 같은 구조를 가집니다:

- `src/`: 소스 코드 (`.cc`, `.h`) 및 `Makefile`
- `report/`: 과제 설명서 (PDF) 및 제출용 압축 파일
- `data/`: 프로그램 실행에 필요한 데이터 파일 (예: `.wav`)
- `build/`: 컴파일된 오브젝트 파일 (`.o`) 및 실행 파일

---

## 📝 과제 개요 (Assignments Overview)

### [Assignment 00](./Assignment00)
- **주제**: 기초 C++ 환경 설정 및 입출력
- **설명**: 두 정수를 입력받아 그 차이의 절댓값을 출력하는 기초적인 프로그램입니다.

### [Assignment 01](./Assignment01)
- **주제**: WAV 오디오 파일 분석 (Peak Amplitude & Silence Detection)
- **설명**: `.wav` 파일을 분석하여 최대 진폭(Peak Amplitude)을 찾고, 일정 시간(0.5초) 이상 지속되는 무음 구간(Silence)을 탐지합니다.
- **주요 기능**:
  - `find_silence` 함수를 통한 무음 구간 탐색
  - 정밀한 진폭 계산 (Short 범위 처리)
  - Address Sanitizer를 이용한 메모리 안정성 확보

### [Assignment 02](./Assignment02)
- **주제**: 수식 트리 구현 및 심볼릭 미분 (Expression Tree & Symbolic Differentiation)
- **설명**: 입력받은 수학 수식을 트리 구조로 파싱하고, 이에 대한 수치 계산 및 심볼릭 미분을 수행합니다.
- **주요 기능**:
  - `int_literal`, `monomial`, `addition`, `multiplication`, `division` 클래스 계층 구조 설계
  - 수식 최적화 (Simplification: $1 \times x \to x$, $0 + x \to x$ 등)
  - 특정 점 $x$에서의 함수값 및 미분계수 계산

---

## 🚀 실행 방법 (How to Run)

모든 과제는 `Makefile`을 통해 빌드할 수 있습니다. 각 과제의 `src` 폴더에서 다음 명령어를 실행하세요.

### Assignment 00
```bash
cd Assignment00/src
make do
./do
# 정수 두 개 입력 (예: 10 20)
```

### Assignment 01
```bash
cd Assignment01/src
make a01
./a01
# 파일명 입력 (예: ../data/s02.wav)
```

### Assignment 02
```bash
cd Assignment02/src
make main
./main
# 수식 입력 (예: x2 + 3*x + 1)
# x 값 입력 (예: 2)
```

---
*본 코드는 학습 목적으로 작성되었습니다.*
