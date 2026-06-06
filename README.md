# STM32 Learning Repository

Code and notes from learning STM32 microcontroller programming, combining materials from several Udemy courses and hands-on experimentation using **STM32 Nucleo-144** and **STM32 Nucleo-32** boards.

## Courses Referenced

1. [Microcontroller Embedded C Programming: Absolute Beginners](https://www.udemy.com/course/microcontroller-embedded-c-programming/) ✅  
   *Completed — certificate included.*

2. [Mastering Microcontroller with Embedded Driver Development](https://www.udemy.com/course/mastering-microcontroller-with-peripheral-driver-development/)  
   *Used selectively — register-level peripheral driver development (SPI, I2C, USART).*

3. [Mastering RTOS: Hands-on with FreeRTOS, Arduino, and STM32Fx](https://www.udemy.com/course/mastering-rtos-hands-on-with-freertos-arduino-and-stm32fx/)  
   *Accessed for FreeRTOS-specific content — task creation, queues, semaphores.*

4. [Mastering Microcontroller: Timers, PWM, CAN, Low Power (MCU2)](https://www.udemy.com/course/microcontroller-programming-stm32-timers-pwm-can-bus-protocol/)  
   *Main reference for Timers, PWM generation, and bxCAN protocol — applied on STM32F446RE and STM32H755ZI.*

## Development Environment

- **Boards:** STM32 Nucleo-144 (F413ZH, H755ZI-Q), STM32 Nucleo-32 (F303K8)
- **Language:** C
- **IDE:** STM32CubeIDE

## Repository Structure

### [`My_workspace/target/`](My_workspace/target/)
Projects running **on the STM32** — course exercises and personal experiments.

| Project | Description |
|---------|-------------|
| `001HelloWorld` | First bare-metal project — UART output |
| `001HelloWorld_semihosting` | Same but with Segger semihosting |
| `003LED` / `004LEDnPIN` | GPIO output — LED blink |
| `006Keypad` | GPIO input — keypad scanning |
| `101Clock` | RCC clock configuration |
| `401–404 FreeRTOS` | FreeRTOS tasks, LED, button with ISR |
| `501Mine_first` | First independent project |
| `502/506 Generating_signals` | Signal generation via DAC + timer |
| `503/505 SD_card` | SPI SD card read/write |

### [`My_workspace/target2/`](My_workspace/target2/)
CAN bus projects on **STM32H755ZI-Q** (dual-core, FDCAN peripheral).

| Project | Description |
|---------|-------------|
| `CAN_LoopBack_course` | bxCAN loopback on STM32F446RE — following MCU2 course |
| `CAN_LoopBack` | FDCAN external loopback on STM32H755ZI-Q — own implementation with TX/RX and UART debug output |

### [`My_workspace/host/`](My_workspace/host/)
C programs running **on the PC** — host-side learning exercises.

| Project | Description |
|---------|-------------|
| `000TestProject` | Basic C host project |
| `001Average` / `002ASCII` / `003Pointers` | C fundamentals exercises |

### [`Datasheets/`](Datasheets/)
Reference documents.

| Folder | Contents |
|--------|----------|
| `c(o)ursed/` | Datasheets for course boards (STM32F407VG Discovery) |
| `mine/` | Datasheets for own boards (Nucleo-F413ZH, Nucleo-H755ZI-Q) |

### [`Other/`](Other/)
Supplementary materials.

| Item | Description |
|------|-------------|
| `0/` | Register address notes and slides from Course 1 |
| `1/` | Additional notes from Course 1 |
| `scratch/` | Scratch code snippets (Segger UART, SystemClock notes) |
| `FreeRTOS11_with_SystemView.pdf` | FreeRTOS + SystemView reference guide |

## Certificate

[View certificate (PDF)](certificate.pdf)
