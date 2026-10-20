"""Hello from Python —— 用来验证解释器、虚拟环境和断点。"""

import platform
import sys


def fib(n: int) -> int:
    if n < 2:
        return n
    return fib(n - 1) + fib(n - 2)


def main() -> None:
    print("Hello from Python!")
    print(f"Python : {platform.python_version()}")
    print(f"解释器 : {sys.executable}")
    print(f"架构   : {platform.machine()}")

    values = [fib(i) for i in range(10)]
    print("fib(0..9) =", values)
    print("sum =", sum(values))


if __name__ == "__main__":
    main()
