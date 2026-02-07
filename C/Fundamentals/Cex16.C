#include <stdio.h>
#include <math.h> /* Required for sqrt() function */

int main() {
    // We use 'double' for higher precision with decimal calculations
    double a, b, c;
    double discriminant, root1, root2, realPart, imagPart;

    printf("=== Quadratic Equation Solver ===\n");
    printf("General Form: ax^2 + bx + c = 0\n\n");

    /* 1. Input Coefficients */
    printf("Enter coefficient a: ");
    scanf("%lf", &a);
    printf("Enter coefficient b: ");
    scanf("%lf", &b);
    printf("Enter coefficient c: ");
    scanf("%lf", &c);

    /* 2. Validation: Check if 'a' is zero */
    // If a is 0, we cannot divide by 2a. It becomes a linear equation bx + c = 0
    if (a == 0) {
        printf("\n[Input Error] Coefficient 'a' cannot be 0 for a quadratic equation.\n");
        printf("This is a linear equation.\n");
        return 1;
    }

    /* 3. Calculate Discriminant */
    // Formula: D = b^2 - 4ac
    discriminant = (b * b) - (4 * a * c);

    printf("\n--- Results ---\n");
    printf("Discriminant (D) = %.2lf\n", discriminant);

    /* 4. Determine the nature of roots */
    
    // Case 1: Real and Distinct Roots (D > 0)
    if (discriminant > 0) {
        // sqrt() is from math.h
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);

        printf("Nature: Roots are Real and Distinct.\n");
        printf("Root 1 = %.2lf\n", root1);
        printf("Root 2 = %.2lf\n", root2);
    }
    
    // Case 2: Real and Equal Roots (D == 0)
    else if (discriminant == 0) {
        root1 = -b / (2 * a);
        
        printf("Nature: Roots are Real and Equal.\n");
        printf("Root 1 = Root 2 = %.2lf\n", root1);
    }
    
    // Case 3: Complex / Imaginary Roots (D < 0)
    else {
        // We cannot square root a negative number directly.
        // We split it into Real Part and Imaginary Part.
        // Real Part = -b / 2a
        // Imaginary Part = sqrt(-D) / 2a
        
        realPart = -b / (2 * a);
        imagPart = sqrt(-discriminant) / (2 * a);

        printf("Nature: Roots are Complex and Imaginary.\n");
        // Output format: x + iy and x - iy
        printf("Root 1 = %.2lf + %.2lfi\n", realPart, imagPart);
        printf("Root 2 = %.2lf - %.2lfi\n", realPart, imagPart);
    }

    return 0;
}