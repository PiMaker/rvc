use crate::math::*;

use alloc::boxed::Box;
use alloc::vec::Vec;

use micromath::F32Ext;

pub struct HitResult {
    distance: f32,
    hit_pos: Vector3,
    normal: Vector3,
    color: Color,
}

pub enum IntersectResult {
    Miss,
    Hit(HitResult),
}

pub trait Intersector {
    fn intersect(&self, origin: &Vector3, direction: &Vector3) -> IntersectResult;
    fn light_intens(&self, res: &HitResult, light: &Light) -> f32;
    fn cast_shadow(&self) -> bool;
    fn receive_shadow(&self) -> bool;
    fn hash(&self) -> u32;
}

pub struct Sphere {
    pub id: u32,
    pub center: Vector3,
    pub radius: f32,
    pub color: Color,
}

pub struct Plane {
    pub id: u32,
    pub position: Vector3,
    pub normal: Vector3,
    pub color: Color,
}

pub struct Light {
    pub position: Vector3,
    pub intensity: f32,
}

impl Intersector for Sphere {
    fn intersect(&self, origin: &Vector3, direction: &Vector3) -> IntersectResult {
        let r = self.radius;
        let c0 = origin - &self.center;

        let a = direction.dot(&direction); // 3
        let half_b = c0.dot(&direction); // -10
        let c = c0.dot(&c0) - r * r; // 75 - 4 = 71

        let disc = half_b * half_b - a * c;
        if disc <= 0.0 {
            return IntersectResult::Miss;
        }

        let disc_sqrt = disc.sqrt();

        let t1 = (-half_b + disc_sqrt) / a;
        let t2 = (-half_b - disc_sqrt) / a;

        let closest = if t1 < 0.0 {
            t2
        } else if t1 < t2 {
            t1
        } else {
            t2
        };
        if closest < 0.001 {
            return IntersectResult::Miss;
        }

        let hit_pos = (direction - origin).normalized() * closest;
        let normal = (&hit_pos - &self.center).normalized();

        IntersectResult::Hit(HitResult {
            distance: closest,
            hit_pos,
            normal,
            color: self.color.clone(),
        })
    }

    fn light_intens(&self, res: &HitResult, light: &Light) -> f32 {
        let dot = res.normal.dot(&light.position) * light.intensity;
        let dot = if dot < 0.04 { 0.04 } else { dot };
        if dot > 0.923 {
            return dot * 18.0;
        }
        if dot > 1.0 {
            1.0
        } else {
            dot
        }
    }

    fn cast_shadow(&self) -> bool {
        true
    }

    fn receive_shadow(&self) -> bool {
        false
    }

    fn hash(&self) -> u32 {
        self.id
    }
}

impl Intersector for Plane {
    fn intersect(&self, origin: &Vector3, direction: &Vector3) -> IntersectResult {
        let den = self.normal.dot(&direction);
        if den.abs() < 0.001 {
            return IntersectResult::Miss;
        }

        let distance = (&self.position - origin).dot(&self.normal) / den;
        if distance < 0.0 {
            return IntersectResult::Miss;
        }

        IntersectResult::Hit(HitResult {
            distance,
            hit_pos: direction * distance,
            normal: self.normal.clone(),
            color: self.color.clone(),
        })
    }

    fn light_intens(&self, res: &HitResult, light: &Light) -> f32 {
        let dir = &light.position - &res.hit_pos;
        let falloff = 26.0 - dir.len();
        let falloff = if falloff < 0.2 { 0.2 } else { falloff };
        falloff * light.intensity
    }

    fn cast_shadow(&self) -> bool {
        false
    }

    fn receive_shadow(&self) -> bool {
        true
    }

    fn hash(&self) -> u32 {
        self.id
    }
}

pub struct Scene {
    objs: Vec<Box<dyn Intersector>>,
    lights: Vec<Light>,
}

impl Scene {
    pub fn new() -> Self {
        Scene {
            objs: Vec::new(),
            lights: Vec::new(),
        }
    }

    pub fn add_obj<I: Intersector + 'static>(&mut self, obj: I) {
        self.objs.push(Box::new(obj));
    }

    pub fn add_light(&mut self, light: Light) {
        self.lights.push(light);
    }

    fn view_vector(x: i32, y: i32, superscale: u32) -> Vector3 {
        Vector3::new(
            x as f32,
            y as f32,
            (crate::FB_WIDTH / superscale / 2) as f32,
        )
        .normalized()
    }

    pub fn raytrace(&self, x: i32, y: i32, superscale: u32) -> Color {
        let view = Self::view_vector(x, y, superscale);
        self.do_raytrace(
            &Vector3::ZERO,
            &view,
            Color { r: 0, g: 0, b: 0 },
            0xffffffff,
        )
    }

    fn do_raytrace(
        &self,
        origin: &Vector3,
        view: &Vector3,
        background: Color,
        ignore_hash: u32,
    ) -> Color {
        let mut closest = IntersectResult::Miss;
        let mut hit_obj = None;

        for obj in &self.objs {
            if obj.hash() == ignore_hash {
                continue;
            }
            let res = obj.intersect(origin, view);
            if let IntersectResult::Hit(HitResult { distance, .. }) = res {
                match closest {
                    IntersectResult::Miss => {
                        closest = res;
                        hit_obj = Some(obj);
                    }
                    IntersectResult::Hit(HitResult {
                        distance: closest_dist,
                        ..
                    }) if closest_dist > distance => {
                        closest = res;
                        hit_obj = Some(obj);
                    }
                    _ => {}
                }
            }
        }

        if let IntersectResult::Hit(res) = closest {
            let hit_obj = hit_obj.unwrap();
            let mut col_out = Color { r: 0, g: 0, b: 0 };
            if res.color.r == 255 && res.color.g == 255 && res.color.b == 255 {
                // mirror
                let invec = view - origin;
                let refl =
                    &(&Vector3::ZERO - &invec) + &(&res.normal * invec.dot(&res.normal) * 2.0);
                let refl = Vector3 {
                    x: -refl.x,
                    y: -refl.y,
                    z: refl.z,
                };
                let rim = if view.dot(&res.normal) < 0.15 { 16 } else { 5 };
                let mirror_color = Color {
                    r: rim,
                    g: rim,
                    b: rim,
                };
                // recurse into mirror space
                let res =
                    self.do_raytrace(&res.hit_pos, &refl, mirror_color.clone(), hit_obj.hash());
                let res = Color {
                    r: res.r.max(mirror_color.r),
                    g: res.g.max(mirror_color.g),
                    b: res.b.max(mirror_color.b),
                };
                return res;
            }
            // calculate lighting
            for light in &self.lights {
                // check if in shadow
                if hit_obj.receive_shadow() {
                    let dir = &light.position - &res.hit_pos;
                    let dir_norm = dir.normalized();
                    let mut shadow = false;
                    for obj in &self.objs {
                        if obj.hash() == hit_obj.hash() || !obj.cast_shadow() {
                            continue;
                        }
                        let res = obj.intersect(&res.hit_pos, &dir_norm);
                        if let IntersectResult::Hit(_) = res {
                            // yep, shadowed
                            shadow = true;
                            break;
                        }
                    }
                    if shadow {
                        // return Color { r: 255, g: 0, b: 0 };
                        continue;
                    }
                }

                let intens = hit_obj.light_intens(&res, light);

                col_out = Color {
                    r: (col_out.r + (res.color.r as f32 * intens) as u32).min(255),
                    g: (col_out.g + (res.color.g as f32 * intens) as u32).min(255),
                    b: (col_out.b + (res.color.b as f32 * intens) as u32).min(255),
                };
            }
            return col_out;
        }

        // black background
        background
    }
}
