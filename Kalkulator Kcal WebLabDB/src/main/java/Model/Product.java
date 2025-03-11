/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Model;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.ToString;

/**
 * Represents a food product containing information about the name,
 * macronutrients (protein, fat, carbohydrates), and total calories.
 * The class calculates the total calories based on the macronutrient content.
 * It provides getter and setter methods for each attribute, allowing 
 * for the management of the product's details.
 *
 * @version 1.1.0
 * @since 1.0
 * @author Patryk Kaszny
 */
@Entity
@Getter @Setter
@AllArgsConstructor
@NoArgsConstructor
@ToString
public class Product {

    /**
     * Conversion factor from grams of protein to calories.
     * (1 gram of protein = 4 kcal).
     */
    static final int CONVERTER_PROTEIN_TO_KCAL = 4;

    /**
     * Conversion factor from grams of fat to calories.
     * (1 gram of fat = 9 kcal).
     */
    static final int CONVERTER_FAT_TO_KCAL = 9;

    /**
     * Conversion factor from grams of carbohydrates to calories.
     * (1 gram of carbohydrate = 4 kcal).
     */
    static final int CONVERTER_CARB_TO_KCAL = 4;

    /**
     * The name of the product.
     */
    @Id
    @Column(name = "name")
    private String name;

    /**
     * The weight of the product, measured in grams.
     */
    @Column(name = "weight", length = 20)
    private int weight;

    /**
     * The amount of protein in the product, measured in grams.
     */
    @Column(name = "protein", length = 20)
    private int protein;

    /**
     * The amount of fat in the product, measured in grams.
     */
    @Column(name = "fat", length = 20)
    private int fat;

    /**
     * The amount of carbohydrates in the product, measured in grams.
     */
    @Column(name = "carb", length = 20)
    private int carb;

    /**
     * The total calories in the product, calculated based on macronutrient content.
     */
    @Column(name = "kcal", length = 20)
    private int kcal;

    /**
     * Constructor to create a new food product, calculating total calories 
     * based on the provided macronutrient values (protein, fat, carbs).
     *
     * @param n the name of the product
     * @param p the amount of protein in grams
     * @param c the amount of carbohydrates in grams
     * @param f the amount of fat in grams
     * @param w the weight of the product in grams
     */
    public Product(String n, int p, int c, int f, int w) {
        this.name = n;
        this.protein = p;
        this.carb = c;
        this.fat = f;
        this.weight = w;

        // Calculate total calories
        this.kcal = this.protein * this.CONVERTER_PROTEIN_TO_KCAL;
        this.kcal += this.fat * this.CONVERTER_FAT_TO_KCAL;
        this.kcal += this.carb * this.CONVERTER_CARB_TO_KCAL;
    }

    /**
     * Returns the amount of protein in the product.
     *
     * @return the amount of protein in grams
     */
    public int getProtein() {
        return this.protein;
    }

    /**
     * Returns the amount of carbohydrates in the product.
     *
     * @return the amount of carbohydrates in grams
     */
    public int getCarb() {
        return this.carb;
    }

    /**
     * Returns the amount of fat in the product.
     *
     * @return the amount of fat in grams
     */
    public int getFat() {
        return this.fat;
    }

    /**
     * Returns the total number of calories in the product.
     *
     * @return the amount of calories in the product
     */
    public int getKcal() {
        return this.kcal;
    }

    /**
     * Returns the name of the product.
     *
     * @return the product name
     */
    public String getName() {
        return this.name;
    }

    /**
     * Returns the weight of the product in grams.
     *
     * @return the weight of the product in grams
     */
    public int getWeight() {
        return this.weight;
    }

    /**
     * Sets the weight of the product in grams.
     *
     * @param newWeight the new weight of the product in grams
     */
    public void setWeight(int newWeight) {
        weight = newWeight;
    }

    /**
     * Sets the amount of protein in the product in grams.
     *
     * @param adjustedProtein the new amount of protein in grams
     */
    public void setProtein(int adjustedProtein) {
        protein = adjustedProtein;
    }

    /**
     * Sets the amount of carbohydrates in the product in grams.
     *
     * @param adjustedCarb the new amount of carbohydrates in grams
     */
    public void setCarb(int adjustedCarb) {
        carb = adjustedCarb;
    }

    /**
     * Sets the amount of fat in the product in grams.
     *
     * @param adjustedFat the new amount of fat in grams
     */
    public void setFat(int adjustedFat) {
        fat = adjustedFat;
    }

    /**
     * Sets the total calories in the product.
     *
     * @param adjustedKcal the new total calories in the product
     */
    public void setKcal(int adjustedKcal) {
        kcal = adjustedKcal;
    }

    /**
     * Sets the weight of the product using a double value.
     * The value will be converted to an integer.
     *
     * @param newWeight the new weight of the product in grams
     */
    public void setWeight(double newWeight) {
        weight = (int) newWeight;
    }

    /**
     * Sets the amount of protein in the product using a double value.
     * The value will be converted to an integer.
     *
     * @param adjustedProtein the new amount of protein in grams
     */
    public void setProtein(double adjustedProtein) {
        protein = (int) adjustedProtein;
    }

    /**
     * Sets the amount of carbohydrates in the product using a double value.
     * The value will be converted to an integer.
     *
     * @param adjustedCarb the new amount of carbohydrates in grams
     */
    public void setCarb(double adjustedCarb) {
        carb = (int) adjustedCarb;
    }

    /**
     * Sets the amount of fat in the product using a double value.
     * The value will be converted to an integer.
     *
     * @param adjustedFat the new amount of fat in grams
     */
    public void setFat(double adjustedFat) {
        fat = (int) adjustedFat;
    }

    /**
     * Sets the total calories in the product using a double value.
     * The value will be converted to an integer.
     *
     * @param adjustedKcal the new total calories in the product
     */
    public void setKcal(double adjustedKcal) {
        kcal = (int) adjustedKcal;
    }

    /**
     * Sets the name of the product.
     *
     * @param newName the new name of the product
     */
    public void setName(String newName) {
        name = newName;
    }

    /**
     * Returns the weight of the product in grams.
     *
     * @return the weight of the product in grams
     */
    public int getGrams() {
        return this.weight;
    }

    /**
     * Returns the total calories in the product.
     *
     * @return the total calories in the product
     */
    public int getCalories() {
        return this.kcal;
    }
}
