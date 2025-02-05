# Study
program vs process vs thread ([https://en.wikipedia.org/wiki/Thread_(computing)#](https://en.wikipedia.org/wiki/Thread_(computing)#))

## Process and Thread

프로세스란 프로그램의 실행이다. 스레드란 프로세스 내 개별 흐름이다.

한 프로그램은 여러 스레드를 가질 수 있다. 각 스레드는 data와 heap 메모리를 공유하지만 각각의 stack 메모리를 가진다.


## The difference between processes and threads
Key Differences Summarized

- **Independence**: Processes are independent and isolated, whereas threads within the same process are not.
- **Memory**: Processes have separate memory spaces, while threads share the same memory space within a process.
- **Communication**: Processes require IPC mechanisms for communication, whereas threads can communicate directly through shared memory.
- **Resource Usage**: Creating and managing processes is more resource-intensive compared to threads.
- **Use Case**: Processes are used for running multiple applications, while threads are used for concurrent tasks within a single application.

When to Use Processes vs. Threads

- **Processes**: Use processes when you need strong isolation between different tasks or applications, such as running different services or applications independently.
- **Threads**: Use threads when you need to perform multiple tasks concurrently within the same application, such as handling multiple user inputs, background tasks, or parallelizing computation.

## pthread는 user level thread? kernel level thread?
https://stackoverflow.com/questions/8639150/is-pthread-library-actually-a-user-thread-solution

## Thread?

<aside>
💡 스레드란?

</aside>

스레드란 한 프로세스내에서의 개별 흐름이다.

한 프로그램은 여러 스레드를 가질 수 있고 실행할 수 있다. 각 스레드는 same global memory (data and heap segments) 와 its own stack 을 가진다.

<aside>
💡 하드웨어스레드와 소프트웨어 스레드란?

</aside>

하드웨어적 스레드란 실제적으로 실행가능한 스레드를 말하고 소프트웨어적 스레드란 가상적으로 가능한 스레드를 말한다. 

예를 들어 상하권이 나뉜 4세트의 책을 생각해보면, 책은 100명이 빌릴 수 있지만 실제로 볼 수 있는 건 8명이다. 여기서 빌릴수 있는 100명이 소프트웨어적 스레드이고 실제로 볼 수 있는 8명이 하드웨어적 스레드이다.

<aside>
💡 스레드 실행순서는 어떻게 되는지?

</aside>

스레드 실행순서는 정해져 있지 않고 Operating system 의 scheduling algorithm에 좌우된다. 

<aside>
💡 atomic operation이란?

</aside>

a+=1 도 atomic 하지 않다. cpu 레지스터에 a의 값을 복사하고 연산한뒤 overwrite를 하기 때문에

atomic하다는 것은 무엇일까? 

atomic하다는 것은 어떤 operation이나 action이 다른 것들에 indivisible하고 uninterruptible하다는 것을 말한다. indivisible하다는 것은 다른 small part로 분리되지 않는다는 것이고 uninterruptible하다는 것은 다른 연산에 방해받지 않는다는 것이다.

reference : https://man7.org/linux/man-pages/man7/pthreads.7.html

## POSIX Safety Concepts?

reference: https://www.gnu.org/software/libc/manual/html_node/POSIX-Safety-Concepts.html

POSIX에서는 asynchronous환경을 지원하기 위해 다음과 같은 것들을 지원한다.

MT-safe, AS-safe, AC-safe.

각각 무엇인지 살펴보기전에 atomic operation과 asynchronous란 무엇인지 알아보자 

<aside>
💡 atomic operations 란?

</aside>

in programming, atomic means uncuttable and indivisible smallest unit. there is no context switching during it. 

<aside>
💡 Asynchronous vs Synchronous 란?


Asynchronous란 위 그림과 같이 순차적으로 실행되는 것이 아니라 동시적으로 실행되는 것을 말한다.

<aside>
💡 MT-Safe 란?

</aside>

함수나 라이브러리가 특정한 환경에서 안전하게 동작되도록 하는 속성이다.

MT-safe(multi-thread-safe)란 멀티스레드환경에서 여러스레드가 동시에 이 함수를 호출해도 함수의 동작이 올바르게 유지되는 것을 의미한다.

어떻게?

내부적으로 mutex를 사용해서 접근을 제어하거나  thread-local-storage를 사용해서 각 스레드가 독립적인 데이터를 가질 수 있게 한다.
For example, having a thread call two MT-Safe functions one right after the other does not guarantee behavior equivalent to atomic execution of a combination of both functions, since concurrent calls in other threads may interfere in a destructive way.

<aside>
💡 AS-safe 란?

</aside>

AS-safe(Asynchronous-signal-safe)란 asynchronous signal handler함수 내에서 함수가 안전하게 호출될 수 있음을 의미한다.

예를들어 _exit함수나 write함수는 비동기적 신호 처리함수 내에서 안전하게 호출될 수 있다.

이러한 함수들은 (reentrant) 함수가 실행중일 때 다시 호출되도 안전하게 호출될 수 있고 호출될 때 공유자원에 대한 접근을 하지않고 손상도 입히지 않는다.

<aside>
💡 AC-safe란?

</aside>

AC-safe(Asynchronous-cancle-safe)란 asynchronous cancellation 시 함수가 안전하게 호출될 수 있음을 의미한다. 비동기 취소(asynchronous cancellation)이란 멀티스레드 환경에서 특정스레드를 강제로 중단시키는 것을 의미한다.

ac-safe속성을 가지는 함수들은 함수 자원에 대해 clean-up을 올바르게 수행하고 중단되는 동안 일관된 상태를 유지한다.

## process ID, parent process ID, process group ID, sessions ID?

<aside>
💡 what is the relationship among process id, parent process id, process group id, sessions id?

</aside>

모든 프로세스는 PID(Process ID)를 가지고 있어, 이를 통해 프로세스를 고유하게 식별할 수 있다. init 프로세스를 제외한 모든 프로세스는 부모 프로세스에서 자식 프로세스로 생성되며, 이를 통해 계층 구조가 만들어진다. 이때 부모 프로세스를 추적하기 위해 PPID(Parent Process ID)가 필요하다.

멀티 프로세스 환경에서는 자식 프로세스를 그룹으로 묶어야 하며, 이때 PGID(Process Group ID)가 사용된다. 같은 그룹에 속하는 프로세스를 관리하기 위한 ID이다. 또한, 여러 프로세스 그룹을 관리하려면 SID(Session ID)가 필요하고, 이를 통해 여러 프로세스를 큰 단위로 묶어 관리할 수 있다.

PID: 각 프로세스를 고유하게 식별하는 ID.

PPID: 부모 프로세스 ID, 프로세스 간 계층 구조 형성.

PGID: 프로세스 그룹 ID, 같은 그룹에 속한 프로세스를 묶어 관리.

SID: 세션 ID, 여러 프로세스 그룹을 묶어 관리.
<aside>
💡 init prcoess?

</aside>

init process는 operating system이 아니다. init process는 커널에 의해 실행된 operating system을 실행하기 위해. init process를 실행하는 이유는 시스템을 초기화하고 시스템 process를 실행하시키며 (operating system) daemon 과 user sessions을 실행시키기 위해서이다.

<aside>
💡 operating system과 kernel , user space의 관계는?

</aside>

operating system은 kernel과 다른 소프트웨어를 포함하고 있다. userspace에서 library function이나 application을 통해 kernal의 system call을 호출하여 하드웨어에 접근할 수 있다.

## 동시성 문제로는 어떤게 있고 어떻게 해결하는지?


1. race condition

경쟁상태란 다중 스레드나 프로세스가 공유자원에 동시에 접근할 때 발생할 수 있는 문제이다. 스레드나 프로세스가 실행순서에 따라 공유자원에 접근하려고 할 때, 그 실행순서에 따라 결과값이 달라질 수 있다.

2. data race

race condition 과 비슷하다. data race란 여러 스레드나 프로세스가 동시에 자원에 접근하면서 적어도 하나가 그 자원에 쓰기를 할 경우에 정의되지 않은 결과가 나올 수 있는 것을 말한다.

3. deadlock

교착 대기란 필요자원이 상대방이 사용하고 있는 것이고 서로 그것을 기다려서 무한정 대기가 발생하는 것을 말한다.

4. 해결 방법

semaphore, mutex, thread scheduling algorithm을 사용해서 우선순위를 부여하거나, 한번에 모든 자원을 갖거나 등으로 해결할 수 있다.

식사하는 철학자 문제를 해결하기 위해서는 다음과 같은 방법을 사용할 수 있다.

1. 홀수번철학자와 짝수번철학자가 왼쪽 오른쪽 포크를 드는 과정을 다르게 하는 것. 

홀수번은 왼쪽들고 오른쪽들고 놓을때는 오른쪽 놓고 왼쪽놓고 짝수번은 반대로 오른쪽들고 왼쪽들고 놓을때는 왼쪽놓고 오른쪽놓게 해서 홀수번과 짝수번의 로직을 다르게 함으로써 교착상태를 해결할 수 있다.

2. 한번에 모든 자원을 획득하는 것. 
3. 이웃 철학자들이 굶주린 시간을 체크해서 우선순위를 부여하는 것.

## Context switching?

Context switching은 CPU가 현재 실행 중인 프로세스나 스레드의 상태를 저장하고, 다른 프로세스나 스레드를 실행하기 위해 해당 상태를 복원하는 과정을 말한다. 이 과정은 운영체제의 스케줄러가 수행하며, 하나의 CPU가 여러 프로세스나 스레드를 효율적으로 처리하기 위해 필수적인 작업이다.

구체적인 과정은 다음과 같다:

상태 저장 (Save context): 실행 중인 프로세스나 스레드의 상태(레지스터 값, 프로그램 카운터 등)를 프로세스 제어 블록(PCB) 또는 스레드 제어 블록(TCB)이라는 구조체에 저장한다.

새로운 작업 선택: 운영체제의 스케줄러가 다음 실행할 프로세스나 스레드를 선택한다. 이때 각 프로세스는 우선순위나 시분할 등의 기준에 따라 선택된다.

상태 복원 (Restore context): 새로운 프로세스나 스레드를 실행하기 위해 그 상태를 PCB나 TCB에서 복원한다. 이때 복원되는 것은 주로 레지스터 값과 프로그램 카운터로, 해당 작업이 이전에 실행되던 상태에서부터 계속 진행될 수 있도록 한다.

이 과정은 매우 빠르게 이루어지며, 멀티태스킹 시스템에서는 이러한 전환이 지속적으로 발생한다. 하지만 이 과정에서 추가적인 시간과 자원이 소모되기 때문에, 지나치게 자주 발생하는 context switching은 성능 저하를 일으킬 수 있다. 특히, 스레드나 프로세스 간의 상태 저장 및 복원에 드는 시간은 시스템 성능에 영향을 미친다.


## How to schedule threads or processes?

1. **선점형 스케줄링 (Preemptive Scheduling)**

- **특징**: 운영 체제가 스레드의 실행을 강제로 중단하고 다른 스레드로 전환할 수 있습니다.
- **장점**: 반응성이 높아 사용자 인터페이스가 부드럽게 동작합니다.
- **단점**: 컨텍스트 스위칭 오버헤드가 발생합니다.
- **예시**: Linux, Windows 등 대부분의 현대 운영 체제

2. **비선점형 스케줄링 (Non-Preemptive Scheduling)**

- **특징**: 스레드가 자발적으로 CPU를 반환할 때까지 실행됩니다.
- **장점**: 컨텍스트 스위칭 오버헤드가 적습니다.
- **단점**: 하나의 스레드가 CPU를 오랫동안 점유할 경우, 다른 스레드의 응답성이 저하됩니다.
- **예시**: 초기 Unix 시스템

## 주요 스케줄링 알고리즘

1. **라운드 로빈 (Round Robin)**

- **방법**: 각 스레드에 동일한 시간 할당량(타임 퀀텀)을 부여하고, 순서대로 실행합니다.
- **특징**: 공정성(fairness)을 보장하며, 반응 시간을 예측할 수 있습니다.
- **적용**: 주로 시간 공유 시스템에서 사용

2. **우선순위 스케줄링 (Priority Scheduling)**

- **방법**: 각 스레드에 우선순위를 부여하고, 높은 우선순위의 스레드가 먼저 실행됩니다.
- **특징**: 중요한 작업을 빠르게 처리할 수 있습니다.
- **문제점**: 우선순위 역전 (Priority Inversion) 문제가 발생할 수 있습니다.
- **적용**: 실시간 시스템, 중요 작업이 있는 환경

3. **다단계 큐 (Multilevel Queue)**

- **방법**: 스레드를 여러 큐로 나누고, 각 큐에 다른 스케줄링 알고리즘을 적용합니다.
- **특징**: 다양한 작업 특성에 맞춘 스케줄링이 가능합니다.
- **적용**: 다양한 작업 특성을 가진 시스템

4. **다단계 피드백 큐 (Multilevel Feedback Queue)**

- **방법**: 스레드가 일정 시간을 사용하면 더 낮은 우선순위 큐로 이동합니다. 반대로, 짧은 시간 내에 완료된 스레드는 높은 우선순위 큐로 이동할 수 있습니다.
- **특징**: 반응성이 높고, 우선순위 조정이 가능합니다.
- **적용**: 다양한 작업 특성을 가진 시스템

5. **최소 잔여 시간 우선 (Shortest Remaining Time First, SRTF)**

- **방법**: 가장 짧은 잔여 실행 시간을 가진 스레드를 먼저 실행합니다.
- **특징**: 평균 대기 시간을 최소화합니다.
- **문제점**: CPU 버스트 시간을 미리 알고 있어야 합니다.
- **적용**: 배치 시스템

6. **공정 공유 스케줄링 (Fair Share Scheduling)**

- **방법**: 자원을 사용자나 그룹 간에 공평하게 분배합니다.
- **특징**: 자원의 공정한 분배를 보장합니다.
- **적용**: 멀티 사용자 시스템

## man(7)

man(7)이란 잡다한 것들 + including macro package and conventions 을 모아놓은 것.

pthred(7)와 같이 포괄적인 개념들을 정리한 내용도 있다.

| **Section** | **주요 내용** | **예시** |
| --- | --- | --- |
| man1 | General Commands | ls, cp, chmod, ... |
| man2 | **System Call** | open, read, write, ... |
| man3 | **Library Functions** | stdio.h |
| man4 | Kernel Interface | 장치, 드라이버, FIFO, socket, 
/dev 내의 형식 관련 규약 등 |
| man5 | File Format | 파일 포맷 규칙
/etc/passwd, /etc/shadow, xinetd.conf 등 |
| man6 | Games |  |
| man7 | Miscellaneous Information | 리눅스 시스템 파일 관련 표준, 규칙, 프로토콜, 문자셋, 시그널 목록 등 |
| man8 | System Manager | root가 사용하는 시스템 관리 관련 명령어 |
| man9 | Kernel Developler | 리눅스 커널 루틴 |

## errno는 자동으로 설정되는지?

system call 이나 function이 실패하면 자동으로 설정됨. 성공하면 갱신되지 않기 때문에 주의필요.
