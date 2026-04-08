//
//  main.swift
//  swenn
//
//  Created by Семён on 11.03.2026.
//  Copyright © 2026 Семён. All rights reserved.
//

import Foundation

func f(_ x: [Double]) -> Double {
    return (log(0.7 * pow(x[0] - 0.6, 4) + 0.2 * pow(x[1] - 0.5, 2) + 0.7 * pow(x[2] - 0.1, 4) + 1))
}

func fx(_ x1: Double, _ x2: Double, _ x3: Double) -> Double {
    return (log(0.7 * pow(x1 - 0.6, 4) + 0.2 * pow(x2 - 0.5, 2) + 0.7 * pow(x3 - 0.1, 4) + 1))
}

func gradF(_ x1: Double, _ x2: Double, _ x3: Double) -> [Double] {
    let den = Double((0.7 * pow(x1 - 0.6, 4) + 0.2 * pow(x2 - 0.5, 2) + 0.7 * pow(x3 - 0.1, 4) + 1))
    let g1 = 4 * (x1 - 0.6) / den
    let g2 = 2 * (x2 - 0.5) / den
    let g3 = 4 * (x3 - 0.1) / den
    let grad: [Double] = [g1, g2, g3]
    
    return grad
}

func plus(_ a: [Double], _ b: [Double]) -> [Double] {
    
    let c1 = a[0] + b[0]
    let c2 = a[1] + b[1]
    let c3 = a[2] + b[2]
    
    let c: [Double] = [c1, c2, c3]
    
    return c
}

func minus(_ a: [Double], _ b: [Double]) -> [Double] {
    
    let c1 = a[0] - b[0]
    let c2 = a[1] - b[1]
    let c3 = a[2] - b[2]
    
    let c: [Double] = [c1, c2, c3]
    
    return c
}

func mult(_ a: [Double], _ x0: Double) -> [Double] {
    
    let c1 = a[0] * x0
    let c2 = a[1] * x0
    let c3 = a[2] * x0
    
    let c: [Double] = [c1, c2, c3]
    
    return c
}

func ScalProd(_ a: [Double], _ b: [Double]) -> Double {
    
    var c = 0.0
    
    for i in 0...2 {
        c = c + a[i] * b[i]
    }
    return c
}

func lenght(_ a: [Double]) -> Double {
    return sqrt(ScalProd(a, a))
}

func swenn(_ x1: Double, _ x2: Double, _ x3: Double, _ d: Double) -> [Double] {
    let x0: Double = 0
    let x: [Double] = [x1, x2, x3]
    
    let x_l = minus(x, mult(gradF(x1, x2, x3), x0 - d))
    let x_c = minus(x, mult(gradF(x1, x2, x3), x0))
    let x_h = minus(x, mult(gradF(x1, x2, x3), x0 + d))
    
    var a: Double = 0
    var b: Double = 0
    
    if (f(x_l) < f(x_c)) && (f(x_c) > f(x_h)) {
        print("Функция не унимодальна")
        return [0, 0]
    }
    else if (f(x_l) > f(x_c)) && (f(x_c) < f(x_h)) {
        a = x0 - d
        b = x0 + d
    }
    else {
        var h: Double = 0
        if (f(x_l) > f(x_c)) && (f(x_c) > f(x_h)) {
            h = d
        } else if (f(x_l) < f(x_c)) && (f(x_c) < f(x_h)) {
            h = -d
        }
        
        var t_prev = x0 - h
        var x_prev = minus(x, mult(gradF(x1, x2, x3), t_prev))
        var t_curr = x0
        var x_curr = minus(x, mult(gradF(x1, x2, x3), t_curr))
        var t_next = x0 + h
        var x_next = minus(x, mult(gradF(x1, x2, x3), t_next))
        
        var k = 0
        while !((f(x_prev) > f(x_curr)) && (f(x_curr) < f(x_next))) {
            h = 2 * h
            t_prev = t_curr
            x_prev = x_curr
            t_curr = t_next
            x_curr = x_next
            t_next = t_curr + h
            x_next = minus(x, mult(gradF(x1, x2, x3), t_next))
            k += 1
            if k > 100 { break }
        }
        
        if h > 0 {
            a = t_prev
            b = t_next
        } else {
            a = t_next
            b = t_prev
        }
    }

    return [a, b]
}

func halfDivision(_ x: [Double], _ grad: [Double], _ ab: [Double], _ eps: Double) -> Double {
    var x0 = ab[0]
    var x4 = ab[1]
    var k = 0
    
    repeat {
        let t1 = (3 * x0 + x4) / 4
        let t2 = (x0 + x4) / 2
        let t3 = (x0 + 3 * x4) / 4
        
        let point1 = minus(x, mult(grad, t1))
        let point2 = minus(x, mult(grad, t2))
        let point3 = minus(x, mult(grad, t3))
        
        let f1 = f(point1)
        let f2 = f(point2)
        let f3 = f(point3)
        
        if (f1 > f2) && (f2 < f3) {
            x0 = t1
            x4 = t3
        } else if (f1 > f2) && (f2 > f3) {
            x0 = t2
        } else if (f1 < f2) && (f2 < f3) {
            x4 = t2
        }
        
        k += 1
    } while (x4 - x0) >= 2 * eps && k < 100
    
    return (x0 + x4) / 2
}

var x1 = 5.317
var x2 = 4.196
var x3 = 3.174
var d = 0

repeat {
    let x_old: [Double] = [x1, x2, x3]
    let ab = swenn(x_old[0], x_old[1], x_old[2], 0.01)
    let grad = gradF(x_old[0], x_old[1], x_old[2])
    let alpha = halfDivision(x_old, grad, ab, 0.0001)
    let x_new = minus(x_old, mult(grad, alpha))
    d += 1
    
    print("Итерация \(d):")
    print(String(format: "find_ab вернул: a = %.4f, b = %.4f", ab[0], ab[1]))
    print(String(format: "alpha = %.4f", alpha))
    print(String(format: "x = %.4f, %.4f, %.4f", x_new[0], x_new[1], x_new[2]))
    print(String(format: "f(x) = %.12f", f(x_new)))
    
    let grad_len = lenght(gradF(x_new[0], x_new[1], x_new[2]))
    let step_len = lenght(minus(x_new, x_old))
    
    print(String(format: "grad = %.6f", grad_len))
    print(String(format: "step = %.6f", step_len))
    
    x1 = x_new[0]
    x2 = x_new[1]
    x3 = x_new[2]
    
    if grad_len < 0.001 || step_len < 0.001 || d > 100 {
        if grad_len < 0.001 { print("\nДостигнута точность по градиенту") }
        if step_len < 0.001 { print("\nДостигнута точность по шагу") }
        if d > 100 { print("\nДостигнуто максимальное число итераций") }
        break
    }
    
    print()
    
} while true
