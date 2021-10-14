use micromath::F32Ext;

#[derive(Clone)]
pub struct Color {
    pub r: u32,
    pub g: u32,
    pub b: u32,
}

impl Color {
    // #[inline(always)]
    // pub fn mix_in(&mut self, other: &Self, mix: f32) {
    //     self.r = lerp(self.r, other.r, mix);
    //     self.g = lerp(self.g, other.g, mix);
    //     self.b = lerp(self.b, other.b, mix);
    // }

    #[inline(always)]
    pub fn to_u128(&self) -> u128 {
        (self.r as u128 * 0xffffff as u128)
            | ((self.g as u128 * 0xffffff as u128) << 32)
            | ((self.b as u128 * 0xffffff as u128) << 64)
            | ((0xffffffff as u128) << 96)
    }
}

#[derive(Clone)]
pub struct Vector3 {
    pub x: f32,
    pub y: f32,
    pub z: f32,
}

impl Vector3 {
    pub const ZERO: Vector3 = Vector3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };
    pub const ONE: Vector3 = Vector3 {
        x: 1.0,
        y: 1.0,
        z: 1.0,
    };

    pub fn new(x: f32, y: f32, z: f32) -> Self {
        Self { x, y, z }
    }

    pub fn dot(&self, rhs: &Self) -> f32 {
        self.x * rhs.x + self.y * rhs.y + self.z * rhs.z
    }

    pub fn len(&self) -> f32 {
        (self.x * self.x + self.y * self.y + self.z * self.z)
            .abs()
            .sqrt()
    }

    pub fn normalized(&self) -> Vector3 {
        let len = self.len();
        Vector3 {
            x: self.x / len,
            y: self.y / len,
            z: self.z / len,
        }
    }
}

impl core::ops::Add for &Vector3 {
    type Output = Vector3;
    fn add(self, rhs: Self) -> Self::Output {
        Vector3::new(self.x + rhs.x, self.y + rhs.y, self.z + rhs.z)
    }
}

impl core::ops::Sub for &Vector3 {
    type Output = Vector3;
    fn sub(self, rhs: Self) -> Self::Output {
        Vector3::new(self.x - rhs.x, self.y - rhs.y, self.z - rhs.z)
    }
}

impl core::ops::Mul<f32> for &Vector3 {
    type Output = Vector3;
    fn mul(self, rhs: f32) -> Self::Output {
        Vector3::new(self.x * rhs, self.y * rhs, self.z * rhs)
    }
}

impl core::ops::Mul<f32> for Vector3 {
    type Output = Vector3;
    fn mul(self, rhs: f32) -> Self::Output {
        Vector3::new(self.x * rhs, self.y * rhs, self.z * rhs)
    }
}

impl core::ops::Div<f32> for &Vector3 {
    type Output = Vector3;
    fn div(self, rhs: f32) -> Self::Output {
        Vector3::new(self.x / rhs, self.y / rhs, self.z / rhs)
    }
}

impl core::ops::Div<f32> for Vector3 {
    type Output = Vector3;
    fn div(self, rhs: f32) -> Self::Output {
        Vector3::new(self.x / rhs, self.y / rhs, self.z / rhs)
    }
}

// pub fn lerp(a: u32, b: u32, n: f32) -> u32 {
//     a + (n * (b - a) as f32) as u32
// }
