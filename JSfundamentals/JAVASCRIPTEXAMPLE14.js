/**
 * PROJECT: Node.js Ray Tracer
 * CONCEPTS: Vector Calculus, Recursion, Lighting Models (Phong), File Encoding
 */

const fs = require('fs');

// --- CONFIGURATION ---
const WIDTH = 800;
const HEIGHT = 600;
const MAX_DEPTH = 3; // How many times light bounces (Reflections)
const OUTPUT_FILE = 'render.ppm';

// --- 1. Vector Math Library ---
// 3D graphics is 90% vector math.
class Vec3 {
    constructor(x, y, z) { this.x = x; this.y = y; this.z = z; }

    static add(v1, v2) { return new Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }
    static sub(v1, v2) { return new Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); }
    static mul(v, n)   { return new Vec3(v.x * n, v.y * n, v.z * n); }
    
    // Dot Product: Calculates angle between two vectors
    static dot(v1, v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
    
    // Normalize: Make vector length equal to 1 (Direction only)
    unit() {
        const len = Math.sqrt(this.x * this.x + this.y * this.y + this.z * this.z);
        return new Vec3(this.x / len, this.y / len, this.z / len);
    }
}

// --- 2. The Scene Objects ---
class Sphere {
    constructor(center, radius, color, specular) {
        this.center = center; // Vec3
        this.radius = radius; // Number
        this.color = color;   // Vec3 (RGB 0-255)
        this.specular = specular; // Shininess (0 = Matte, 1000 = Mirror)
    }
}

class Light {
    constructor(type, intensity, position) {
        this.type = type; // 'ambient', 'point'
        this.intensity = intensity;
        this.position = position;
    }
}

// --- 3. The World Definition ---
const spheres = [
    new Sphere(new Vec3(0, -1, 3), 1, new Vec3(255, 0, 0), 500),    // Red Sphere
    new Sphere(new Vec3(2, 0, 4), 1, new Vec3(0, 0, 255), 500),     // Blue Sphere
    new Sphere(new Vec3(-2, 0, 4), 1, new Vec3(0, 255, 0), 10),     // Green Sphere
    new Sphere(new Vec3(0, -5001, 0), 5000, new Vec3(255, 255, 0), 1000) // Yellow Floor
];

const lights = [
    new Light('ambient', 0.2, null),
    new Light('point', 0.6, new Vec3(2, 1, 0)),
    new Light('point', 0.2, new Vec3(1, 4, 4))
];

// --- 4. The Physics Engine ---

// Solves Quadratic Equation to find if Ray hits Sphere
function intersectRaySphere(origin, direction, sphere) {
    const oc = Vec3.sub(origin, sphere.center);
    
    const k1 = Vec3.dot(direction, direction);
    const k2 = 2 * Vec3.dot(oc, direction);
    const k3 = Vec3.dot(oc, oc) - sphere.radius * sphere.radius;

    const discriminant = k2 * k2 - 4 * k1 * k3;
    if (discriminant < 0) return [Infinity, Infinity];

    const t1 = (-k2 + Math.sqrt(discriminant)) / (2 * k1);
    const t2 = (-k2 - Math.sqrt(discriminant)) / (2 * k1);
    return [t1, t2];
}

// Calculate Lighting & Shadows
function computeLighting(point, normal, viewVec, specular) {
    let intensity = 0;
    
    for (let light of lights) {
        if (light.type === 'ambient') {
            intensity += light.intensity;
        } else {
            let vecToLight = Vec3.sub(light.position, point);
            const distToLight = Math.sqrt(Vec3.dot(vecToLight, vecToLight));
            
            // Shadow Check: Can we see the light or is an object in the way?
            // (We assume shadows are binary: either lit or dark)
            // Real ray tracers would check intersections here.
            
            vecToLight = vecToLight.unit();
            const n_dot_l = Vec3.dot(normal, vecToLight);

            // Diffuse (Matte)
            if (n_dot_l > 0) {
                intensity += light.intensity * n_dot_l;
            }

            // Specular (Shiny Reflection)
            if (specular > 0) {
                const vecReflect = Vec3.sub(Vec3.mul(normal, 2 * n_dot_l), vecToLight);
                const r_dot_v = Vec3.dot(vecReflect, viewVec);
                if (r_dot_v > 0) {
                    intensity += light.intensity * Math.pow(r_dot_v / (Math.sqrt(Vec3.dot(vecReflect,vecReflect)) * Math.sqrt(Vec3.dot(viewVec,viewVec))), specular);
                }
            }
        }
    }
    return intensity;
}

// Main Tracing Function (Recursive)
function traceRay(origin, direction, min_t, max_t, recursion_depth) {
    let closest_t = Infinity;
    let closest_sphere = null;

    // Find nearest object
    for (let sphere of spheres) {
        const [t1, t2] = intersectRaySphere(origin, direction, sphere);
        if (t1 > min_t && t1 < max_t && t1 < closest_t) {
            closest_t = t1;
            closest_sphere = sphere;
        }
        if (t2 > min_t && t2 < max_t && t2 < closest_t) {
            closest_t = t2;
            closest_sphere = sphere;
        }
    }

    if (closest_sphere == null) return new Vec3(0, 0, 0); // Black Background

    // Calculate Point and Normal
    const point = Vec3.add(origin, Vec3.mul(direction, closest_t));
    let normal = Vec3.sub(point, closest_sphere.center);
    normal = normal.unit();
    
    const viewVec = Vec3.mul(direction, -1);

    // Calculate Color
    const lighting = computeLighting(point, normal, viewVec, closest_sphere.specular);
    const localColor = Vec3.mul(closest_sphere.color, lighting);

    // Reflection (Recursion)
    // If we hit a shiny object and haven't bounced too many times...
    const r = closest_sphere.specular / 1000; // Reflectivity (0.0 - 1.0)
    if (recursion_depth <= 0 || r <= 0) {
        return localColor;
    }

    // Calculate Reflection Ray
    // R = 2*N*dot(N,V) - V
    const rayReflect = Vec3.sub(Vec3.mul(normal, 2 * Vec3.dot(normal, viewVec)), viewVec);
    const reflectedColor = traceRay(point, rayReflect, 0.001, Infinity, recursion_depth - 1);

    // Mix Local Color + Reflected Color
    return Vec3.add(Vec3.mul(localColor, 1 - r), Vec3.mul(reflectedColor, r));
}

// --- 5. Rendering Loop ---
console.log(`\n--- RAYTRACE STUDIO ---`);
console.log(`Rendering ${WIDTH}x${HEIGHT} scene...`);

let buffer = `P3\n${WIDTH} ${HEIGHT}\n255\n`; // PPM Header

const origin = new Vec3(0, 0, 0); // Camera Position

for (let y = HEIGHT / 2; y > -HEIGHT / 2; y--) {
    
    // Progress Bar
    if (y % 50 === 0) process.stdout.write(`\rLines remaining: ${y + HEIGHT/2}   `);

    for (let x = -WIDTH / 2; x < WIDTH / 2; x++) {
        // Convert pixel coordinate to viewport coordinate
        const direction = new Vec3(x / WIDTH, y / HEIGHT, 1).unit(); // 1 = distance to viewport plane
        
        // Shoot the ray!
        let color = traceRay(origin, direction, 1, Infinity, MAX_DEPTH);
        
        // Clamp color to 0-255
        const r = Math.min(255, Math.max(0, Math.floor(color.x)));
        const g = Math.min(255, Math.max(0, Math.floor(color.y)));
        const b = Math.min(255, Math.max(0, Math.floor(color.z)));

        buffer += `${r} ${g} ${b} `;
    }
    buffer += "\n";
}

fs.writeFileSync(OUTPUT_FILE, buffer);
console.log(`\n\n✅ Render Complete! Saved to '${OUTPUT_FILE}'`);
console.log(`ℹ️  Note: You can view this file online at https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html`);
console.log(`    Or convert it using GIMP/Photoshop/Magick.`);