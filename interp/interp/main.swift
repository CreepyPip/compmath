//
//  main.swift
//  interp
//
//  Created by Семён Зайцев on 06.05.2026.
//

import Foundation

func p(_ x: [Double],_ y: [Double]) -> [[Double]] {
    let p0:[Double] = [1, x[0], pow(x[0], 2), pow(x[0], 3), pow(x[0], 4), pow(x[0], 5), y[0]]
    let p1:[Double] = [1, x[1], pow(x[1], 2), pow(x[1], 3), pow(x[1], 4), pow(x[1], 5), y[1]]
    let p2:[Double] = [1, x[2], pow(x[2], 2), pow(x[2], 3), pow(x[2], 4), pow(x[2], 5), y[2]]
    let p3:[Double] = [1, x[3], pow(x[3], 2), pow(x[3], 3), pow(x[3], 4), pow(x[3], 5), y[3]]
    let p4:[Double] = [1, x[4], pow(x[4], 2), pow(x[4], 3), pow(x[4], 4), pow(x[4], 5), y[4]]
    let p5:[Double] = [1, x[5], pow(x[5], 2), pow(x[5], 3), pow(x[5], 4), pow(x[5], 5), y[5]]
    return [p0, p1, p2, p3, p4, p5]
}

func jgauss(_ p: [[Double]]) -> [[Double]] {
    var a = p
    let n = a.count
    let m = a[0].count
    
    for k in 0..<n {
        var maxRow = k
        var maxVal = abs(a[k][k])
        for i in (k+1)..<n {
            let val = abs(a[i][k])
            if val > maxVal {
                maxVal = val
                maxRow = i
            }
        }
        
        if maxRow != k {
            a.swapAt(k, maxRow)
        }
        
        let div = a[k][k]
        for j in k..<m {
            a[k][j] /= div
        }
        
        for i in 0..<n {
            if i != k {
                let f = a[i][k]
                if f != 0 {
                    for j in k..<m {
                        a[i][j] -= f * a[k][j]
                    }
                }
            }
        }
    }
    
    return a
}

func lagrange(_ x: [Double], _ y: [Double]) -> [Double] {
    let n = x.count
    var coeffs = [Double](repeating: 0.0, count: n)
    
    for i in 0..<n {
        var num = [1.0]
        var denom = 1.0
        
        for j in 0..<n where j != i {
            var newNum = [Double](repeating: 0.0, count: num.count + 1)
            for k in 0..<num.count {
                newNum[k] += num[k] * (-x[j])
                newNum[k+1] += num[k]
            }
            num = newNum
            denom *= (x[i] - x[j])
        }
            
        let factor = y[i] / denom
        for k in 0..<num.count {
            coeffs[k] += factor * num[k]
        }
    }
    return coeffs
}

func newton(_ x: [Double], _ y: [Double]) -> [Double] {
    let n = x.count
    var dd = y
    
    for j in 1..<n {
        for i in stride(from: n-1, through: j, by: -1) {
            dd[i] = (dd[i] - dd[i-1]) / (x[i] - x[i-j])
        }
    }
    
    var coeffs = [Double](repeating: 0.0, count: n)
    for k in 0..<n {
        var poly = [1.0]
        for j in 0..<k {
            var newPoly = [Double](repeating: 0.0, count: poly.count + 1)
            for t in 0..<poly.count {
                newPoly[t] += poly[t] * (-x[j])
                newPoly[t+1] += poly[t]
            }
            poly = newPoly
        }
        let c = dd[k]
        for t in 0..<poly.count {
            coeffs[t] += c * poly[t]
        }
    }
    return coeffs
}

let x: [Double] = [-5, -2, 1, 4, 7, 10]
let y: [Double] = [4, -2, 2, -4, 7, -7]

let res = jgauss(p(x, y))

print("Жорданн - Гаусс")
for i in 0..<5 {
    print(String(format:"x\(i) %.3f", res[0][6]+res[1][6]*x[i]+res[2][6]*pow(x[i], 2)+res[3][6]*pow(x[i], 3)+res[4][6] * pow(x[i], 4)+res[5][6]*pow(x[i], 5)))
}

let res2 = lagrange(x, y)

print("Лагранж")
for i in 0..<5 {
    print(String(format:"x\(i) %.3f", res2[0]+res2[1]*x[i]+res2[2]*pow(x[i], 2)+res2[3]*pow(x[i], 3)+res2[4]*pow(x[i], 4)+res2[5]*pow(x[i], 5)))
}

let res3 = newton(x, y)

print("Ньютон")
for i in 0..<5 {
    print(String(format:"x\(i) %.3f", res3[0]+res3[1]*x[i]+res3[2]*pow(x[i], 2)+res3[3]*pow(x[i], 3)+res3[4]*pow(x[i], 4)+res3[5]*pow(x[i], 5)))
}
