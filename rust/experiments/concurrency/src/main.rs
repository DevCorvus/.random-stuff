use std::{
    sync::{mpsc, Arc, Mutex},
    thread,
    time::Duration,
};

fn channels() {
    let (tx, rx) = mpsc::channel();

    let tx_copy = tx.clone();
    thread::spawn(move || {
        tx_copy.send(String::from("UwU")).unwrap();
        thread::sleep(Duration::from_millis(500));
    });

    thread::spawn(move || {
        tx.send(String::from("OwO")).unwrap();
        thread::sleep(Duration::from_secs(1));
    });

    for message in rx {
        println!("{}", message);
    }
}

fn shared_state() {
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..10 {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap();
            *num += 1;
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Result: {}", *counter.lock().unwrap());
}

fn main() {
    channels();
    shared_state();
}
