use glium::{
    glutin::{
        dpi::LogicalSize,
        event::{Event, StartCause, WindowEvent},
        event_loop::{ControlFlow, EventLoop},
        window::WindowBuilder,
        ContextBuilder,
    },
    index::{NoIndices, PrimitiveType},
    Display, Program, Surface, VertexBuffer,
};
use std::time::{Duration, Instant};

#[macro_use]
extern crate glium;

fn main() {
    let events_loop = EventLoop::new();
    let wb = WindowBuilder::new()
        .with_inner_size(LogicalSize::new(800.0, 600.0))
        .with_title("Hello world");
    let cb = ContextBuilder::new();
    let display = Display::new(wb, cb, &events_loop).unwrap();

    #[derive(Copy, Clone)]
    struct Vertex {
        position: [f32; 2],
    }

    implement_vertex!(Vertex, position);

    let shape = vec![
        Vertex {
            position: [-0.5, -0.5],
        },
        Vertex {
            position: [0.0, 0.5],
        },
        Vertex {
            position: [0.5, -0.25],
        },
    ];

    let vertex_buffer = VertexBuffer::new(&display, &shape).unwrap();
    let indices = NoIndices(PrimitiveType::TrianglesList);

    let vertex_shader_src = r#"
        #version 140

        in vec2 position;
        // uniform float t;
        uniform mat4 matrix;

        void main() {
            // vec2 pos = position;
            // pos.x += t;
            // gl_Position = vec4(pos, 0.0, 1.0);
            gl_Position = matrix * vec4(position, 0.0, 1.0);
        }
    "#;

    let fragment_shader_src = r#"
        #version 140

        out vec4 color;

        void main() {
            color = vec4(1.0, 0.0, 0.0, 1.0);
        }
    "#;

    let program =
        Program::from_source(&display, vertex_shader_src, fragment_shader_src, None).unwrap();

    let mut t: f32 = -0.5;
    events_loop.run(move |event, _, control_flow| {
        let next_frame_time = Instant::now() + Duration::from_nanos(16_666_667);
        *control_flow = ControlFlow::WaitUntil(next_frame_time);

        match event {
            Event::WindowEvent { event, .. } => match event {
                WindowEvent::CloseRequested => {
                    *control_flow = ControlFlow::Exit;
                    return;
                }
                _ => return,
            },
            Event::NewEvents(cause) => match cause {
                StartCause::ResumeTimeReached { .. } => (),
                StartCause::Init => (),
                _ => return,
            },
            _ => (),
        }

        println!("{t}");

        t += 0.0010;
        if t > 0.5 {
            t = -0.5;
        }

        let mut target = display.draw();
        target.clear_color(0.0, 0.0, 1.0, 1.0);
        // let uniforms = uniform! { t: t };
        let uniforms = uniform! {
            matrix: [
                [t.cos(), t.sin(), 0.0, 0.0],
                [-t.sin(), t.cos(), 0.0, 0.0],
                [0.0, 0.0, 1.0, 0.0],
                [0.0, 0.0, 0.0, 1.0f32],
            ]
        };
        target
            .draw(
                &vertex_buffer,
                &indices,
                &program,
                &uniforms,
                &Default::default(),
            )
            .unwrap();
        target.finish().unwrap();
    });
}
