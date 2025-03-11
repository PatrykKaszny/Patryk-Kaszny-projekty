package pl.polsl.lab.model;

import Model.Agregacja;
import Model.Product;
import java.util.ArrayList;
import java.util.List;

/**
 * Singleton class that provides access to a single instance of the Agregacja model.
 * This class ensures that the Agregacja instance is created only once and provides 
 * methods for interacting with the product and consumed product data.
 * 
 * @version 1.0.0
 * @since 1.0
 * @author Patryk Kaszny
 */
public class SingletonModel {

    private static Agregacja instance;

    /**
     * Private constructor to prevent instantiation of the Singleton class.
     * The constructor initializes the Agregacja instance and adds some default products.
     */
    private SingletonModel() {  
    }

    /**
     * Provides access to the unique instance of the Agregacja class. 
     * If the instance is not yet created, it will be initialized with some default products.
     * 
     * @return the instance of Agregacja
     */
    public static Agregacja getInstance() {

       if(instance == null) {
            instance = new Agregacja();
            
        }
        return instance;
    }

    /**
     * Updates the product details in the Agregacja instance.
     * 
     * @param id the index of the product to update
     * @param updatedProduct the updated product details
     * @return true if the product was successfully updated, false otherwise
     */
    public boolean updateProduct(int id, Product updatedProduct) {
        return instance.updateProduct(id, updatedProduct);
    }

    /**
     * Adds a consumed product to the list of eaten products.
     * 
     * @param name the name of the consumed product
     * @param grams the weight of the consumed product in grams
     * @param calories the number of calories in the consumed product
     * @param protein the amount of protein in the consumed product (in grams)
     * @param carbs the amount of carbohydrates in the consumed product (in grams)
     * @param fat the amount of fat in the consumed product (in grams)
     */
    public void addConsumedProduct(String name, int grams, int calories, int protein, int carbs, int fat) {
        instance.addEatenProducts(name, grams, calories, protein, carbs, fat);
    }
}
