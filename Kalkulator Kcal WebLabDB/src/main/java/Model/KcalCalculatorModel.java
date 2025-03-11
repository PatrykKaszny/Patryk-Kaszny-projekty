/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Calorie calculator model, which stores a list of all products and consumed
 * products along with their nutritional values. Allows reading and writing
 * products to/from a file, and adding or removing products.
 *
 * @version 1.1.0
 * @since 1.0
 * @author Patryk Kaszny
 */
public class KcalCalculatorModel {

    private final List<Product> allProducts = Collections.synchronizedList(new ArrayList<>());
    private final List<Product> eatenProducts = Collections.synchronizedList(new ArrayList<>());

    private int allKcal;
    private int allProtein;
    private int allFat;
    private int allCarb;

    /**
     * Default constructor, initializing nutritional values to 0.
     */
    public KcalCalculatorModel() {
        allKcal = 0;
        allProtein = 0;
        allFat = 0;
        allCarb = 0;
    }

    /**
     * Adds a product to the list of all products.
     *
     * @param p the product to be added
     */
    public void addToAllProducts(Product p) {
        this.allProducts.add(p);
    }

    /**
     * Removes a product from the list of all products by index.
     *
     * @param n the index of the product to be removed
     * @return true if the product was removed, false otherwise
     */
    public boolean removeFromAllProducts(int n) {
        if ((n >= 0) && (n < allProducts.size())) {
            this.allProducts.remove(n);
            return true;
        }
        return false;
    }

    /**
     * Adds a product to the list of consumed products and updates total
     * nutritional values.
     *
     * @param name Name of the consumed product
     * @param grams Weight of the consumed product in grams
     * @param protein Protein value of the product
     * @param carbs Carbohydrate value of the product
     * @param fat Fat value of the product
     */
    public void addToEatenProducts(String name, int grams, int protein, int carbs, int fat) {
        Product prod = new Product(name, protein, carbs, fat, grams);
        this.eatenProducts.add(prod);

        this.allKcal += prod.getKcal();
        this.allProtein += protein;
        this.allCarb += carbs;
        this.allFat += fat;
    }

    /**
     * Removes a product from the list of consumed products by index and updates
     * total nutritional values.
     *
     * @param n The index of the product to remove
     */
    public void removeFromEatenProducts(int n) {
        this.allKcal -= this.eatenProducts.get(n).getKcal();
        this.allProtein -= this.eatenProducts.get(n).getProtein();
        this.allCarb -= this.eatenProducts.get(n).getCarb();
        this.allFat -= this.eatenProducts.get(n).getFat();
        this.eatenProducts.remove(n);
    }

    /**
     * Returns the total nutritional values of consumed products: calories,
     * protein, fat, and carbs.
     *
     * @return Array with nutritional values (calories, protein, fat, carbs)
     */
    public int[] getMakro() {
        int[] makro = {this.allKcal, this.allProtein, this.allFat, this.allCarb};
        return makro;
    }

    /**
     * Returns the list of all products.
     *
     * @return List of all products
     */
    public List<Product> getAllProduct() {
        return this.allProducts;
    }

    /**
     * Returns the list of consumed products.
     *
     * @return List of consumed products
     */
    public List<Product> getEatenProduct() {
        return this.eatenProducts;
    }

    /**
     * Updates the consumed product's weight and recalculates its nutritional values
     * based on the new weight.
     *
     * @param i The index of the product in the list of consumed products
     * @param newWeight The new weight of the consumed product
     */
    public void updateFromEatenProducts(int i, double newWeight) {
        double k = (double) (newWeight / eatenProducts.get(i).getWeight());
        System.out.println("Kcal d" + (k * eatenProducts.get(i).getKcal()));
        System.out.println("Kcal i" + (int) (k * eatenProducts.get(i).getKcal()));
        eatenProducts.get(i).setKcal((k * eatenProducts.get(i).getKcal()));
        System.out.println("Kcal po" + (eatenProducts.get(i).getKcal()));
        eatenProducts.get(i).setProtein((k * eatenProducts.get(i).getProtein()));
        eatenProducts.get(i).setFat((k * eatenProducts.get(i).getFat()));
        eatenProducts.get(i).setCarb((k * eatenProducts.get(i).getCarb()));
        eatenProducts.get(i).setWeight(newWeight);
    }
}
