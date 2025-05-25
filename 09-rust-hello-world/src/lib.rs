#![no_std]
#![feature(allocator_api, global_asm)]

use kernel::prelude::*;

module! {
    type: HelloWorld,
    name: b"hello_world",
    author: b"Your Name",
    description: b"A simple Hello World kernel module in Rust",
    license: b"GPL",
}

struct HelloWorld;

impl KernelModule for HelloWorld {
    fn init() -> Result<Self> {
        pr_info!("Hello, world from Rust kernel module!\n");
        Ok(HelloWorld)
    }
}

impl Drop for HelloWorld {
    fn drop(&mut self) {
        pr_info!("Goodbye, world from Rust kernel module!\n");
    }
}

