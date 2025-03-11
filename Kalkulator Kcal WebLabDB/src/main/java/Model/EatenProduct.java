package Model;

import jakarta.persistence.CascadeType;
import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.ManyToOne;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.ToString;

/**
 * Represents an instance of a product being eaten, storing specific details 
 * such as the amount consumed and the associated product.
 * This entity is used to track the consumption of products in terms of weight 
 * and calories for analysis and reporting purposes.
 *
 * @version 1.0.0
 * @since 1.0
 * @author Patryk Kaszny
 */
@Entity
@Getter @Setter
@AllArgsConstructor
@NoArgsConstructor
@ToString
public class EatenProduct {

    /**
     * The unique identifier of the eaten product.
     */
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    /**
     * The amount of the product consumed, measured in grams.
     */
    @Column(name = "amount")
    private int amount;

    /**
     * The total calories consumed based on the amount of the product eaten.
     */
    @Column(name = "totalKcal")
    private int totalKcal;

    /**
     * The product associated with this consumption entry. 
     * It represents the actual product consumed.
     */
    @ManyToOne(cascade = {CascadeType.PERSIST})
    public Product product;

    /**
     * Constructor to create a new EatenProduct based on an existing product 
     * and the amount consumed. The total calories are automatically calculated 
     * based on the product's properties and the amount eaten.
     *
     * @param product the product that was consumed
     * @param amount the amount of the product consumed, in grams
     */
    public EatenProduct(Product product, int amount) {
        this.product = product;
        this.amount = amount;
        this.totalKcal = calculateCalories(product, amount);
    }
    
    /**
     * Constructor to create an EatenProduct with manually provided details 
     * such as the product name, grams consumed, and calories consumed. 
     * The calories are set directly from the provided input.
     *
     * @param Name the name of the product
     * @param grams the amount of the product consumed, in grams
     * @param kcal the total calories consumed for the given amount of product
     * @param p the amount of protein in the product (in grams)
     * @param c the amount of carbohydrates in the product (in grams)
     * @param f the amount of fat in the product (in grams)
     */
    public EatenProduct(String Name, int grams, int kcal, int p, int c, int f) {
        this.product = new Product(Name, p, c, f, grams);
        this.totalKcal = kcal;
    }

    /**
     * Calculates the total number of calories consumed based on the product's 
     * nutritional information and the amount consumed. This method assumes 
     * the product has a weight property and a calorie content per unit weight.
     *
     * @param product the product being consumed
     * @param amount the amount of the product consumed, in grams
     * @return the total number of calories consumed based on the product's 
     *         caloric value and the amount consumed
     */
    private int calculateCalories(Product product, int amount) {
        // Calculate the ratio of the consumed amount to the product's weight
        double ratio = (double) amount / product.getWeight();
        // Return the total calories by multiplying the ratio by the product's total calories
        return (int) (product.getKcal() * ratio);
    }
}
