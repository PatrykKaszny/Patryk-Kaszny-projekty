/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Model;

import java.util.List;
import pl.polsl.lab.model.DatabaseSource;

/**
 * The Agregacja class manages products and consumed products,
 * allowing for operations like adding, removing, updating products and handling their weight.
 * It delegates data management to the KcalCalculatorModel class.
 *
 * @version 1.1.0
 * @since 1.0
 * @author Patryk Kaszny
 */
public class Agregacja {
     private KcalCalculatorModel calc = new KcalCalculatorModel();
    
    

    public Agregacja() {
        // Constructor initializes the KcalCalculatorModel
    }

    /**
     * Retrieves all products from the KcalCalculatorModel.
     * 
     * @return List of all products
     */
    public List<Product> getAllProductList() {
        return calc.getAllProduct();
    }

    /**
     * Retrieves all eaten products from the KcalCalculatorModel.
     * 
     * @return List of all eaten products
     */
    public List<Product> getEatenProductList() {
        return calc.getEatenProduct();
    }

    /**
     * Adds a new product to the list of all products.
     * 
     * @param name Name of the product
     * @param protein Amount of protein in the product
     * @param carb Amount of carbohydrates in the product
     * @param fat Amount of fat in the product
     */
    public void addToAllProducts(String name, int protein, int carb, int fat) {
        Product p = new Product(name, protein, carb, fat, 100);
        calc.addToAllProducts(p);
    }

    /**
     * Removes a product by its ID from the list of all products.
     * 
     * @param id The ID of the product to remove
     * @return true if the product was removed, false otherwise
     */
    public boolean removeProductById(int id) {
        System.out.println("Usuwam produkt " + id);
        return calc.removeFromAllProducts(id);
    }

    /**
     * Updates a product in the list of all products by its ID.
     * 
     * @param id The ID of the product to update
     * @param updatedProduct The updated product object
     * @return true if the product was updated, false otherwise
     */
    public boolean updateProduct(int id, Product updatedProduct) {
        List<Product> products = calc.getAllProduct();
        if (id < 0 || id >= products.size()) {
            return false;
        }
        products.set(id, updatedProduct);
        return true;
    }

    /**
     * Adds a consumed product to the list of eaten products.
     * 
     * @param name Name of the consumed product
     * @param grams Amount of product consumed in grams
     * @param calories Calories consumed
     * @param protein Amount of protein consumed
     * @param carbs Amount of carbohydrates consumed
     * @param fat Amount of fat consumed
     */
    public void addEatenProducts(String name, int grams, int calories, int protein, int carbs, int fat) {
        calc.addToEatenProducts(name, grams, protein, carbs, fat);
    }

    /**
     * Removes a consumed product by its ID from the list of eaten products.
     * 
     * @param productId The ID of the product to remove
     * @return true if the product was removed, false otherwise
     */
    public boolean removeConsumedProductById(int productId) {
        List<Product> eatenProducts = getEatenProductList();
        if (productId >= 0 && productId < eatenProducts.size()) {
            eatenProducts.remove(productId);
            return true;
        }
        return false;
    }

    /**
     * Retrieves a consumed product by its ID.
     * 
     * @param productId The ID of the consumed product
     * @return The consumed product if found, null otherwise
     */
    public Product getConsumedProductById(int productId) {
        return calc.getEatenProduct().get(productId);
    }

    /**
     * Updates a consumed product in the list of eaten products.
     * This method updates the product based on its name.
     * 
     * @param product The updated product object
     * @return true if the product was updated, false otherwise
     */
    public boolean updateConsumedProduct(Product product) {
        for (int i = 0; i < calc.getEatenProduct().size(); i++) {
            if (calc.getEatenProduct().get(i).getName().equals(product.getName())) {
                calc.getEatenProduct().set(i, product);
                return true;
            }
        }
        return false;
    }

    /**
     * Removes a product from the list of eaten products by its index.
     * 
     * @param index The index of the product to remove
     * @return true if the product was removed, false otherwise
     */
    public boolean removeProductFromEatenList(int index) {
        List<Product> eatenProducts = getEatenProductList();
        if (index >= 0 && index < eatenProducts.size()) {
            eatenProducts.remove(index);
            return true;
        }
        return false;
    }

    /**
     * Removes a product from the eaten products list by its name.
     * 
     * @param productName The name of the product to remove
     */
    public void removeEatenProductList(String productName) {
        List<Product> eatenProducts = calc.getEatenProduct();
        for (int i = 0; i < eatenProducts.size(); i++) {
            if (eatenProducts.get(i).getName().equals(productName)) {
                calc.removeFromEatenProducts(i);
                break;
            }
        }
    }

    /**
     * Updates the weight of a consumed product by its name.
     * 
     * @param productName The name of the product to update
     * @param newWeight The new weight for the product
     * @return The updated product if found, null otherwise
     */
    public Product updateProductWeight(String productName, int newWeight) {
        List<Product> eatenProducts = calc.getEatenProduct();
        for (int i = 0; i < eatenProducts.size(); i++) {
            if (eatenProducts.get(i).getName().equals(productName)) {
                calc.updateFromEatenProducts(i, newWeight);
                return eatenProducts.get(i);
            }
        }
        return null;
    }

    public class databaseSource {

        public databaseSource() {
        }
    }
}
