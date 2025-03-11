package pl.polsl.lab.model;

import Model.EatenProduct;
import Model.Product;
import java.util.List;

/**
 * Interface defining the contract for data source operations related to 
 * products and eaten products. It provides methods for retrieving, updating, 
 * and deleting products, as well as persisting objects and managing eaten products.
 * 
 * The implementation of this interface handles the actual data storage, whether 
 * it's in memory, a database, or any other persistent storage mechanism.
 * 
 * @version 1.1.0
 * @since 1.0
 * @author Patryk Kaszny
 */
public interface DataSource {

    /**
     * Retrieves the list of all products stored in the data source.
     * 
     * @return a List of Product objects representing all products in the data source
     */
    public List<Product> getProductList();

    /**
     * Updates the details of a given product in the data source.
     * 
     * @param product the Product object to update
     * @return true if the product was successfully updated, false otherwise
     */
    public boolean update(Product product);

    /**
     * Deletes a product from the data source based on its name.
     * 
     * @param name the name of the product to delete
     * @return true if the product was successfully deleted, false otherwise
     */
    public boolean delete(String Name);

    /**
     * Persists a given object in the data source. This could be used to save 
     * new data or update existing data.
     * 
     * @param object the object to persist
     */
    public void persistObject(Object object);

    /**
     * Retrieves the list of all eaten products stored in the data source.
     * 
     * @return a List of EatenProduct objects representing all eaten products
     *         in the data source
     */
    public List<EatenProduct> getEatenProductList();

    /**
     * Updates the details of a given eaten product in the data source.
     * 
     * @param product the EatenProduct object to update
     * @return true if the eaten product was successfully updated, false otherwise
     */
    public boolean updateEatenProduct(EatenProduct product);

    /**
     * Deletes an eaten product from the data source based on its name.
     * 
     * @param name the name of the eaten product to delete
     * @return true if the eaten product was successfully deleted, false otherwise
     */
    public boolean deleteEatenProduct(String name);

    /**
     * Updates the amount of an eaten product in the data source.
     * 
     * @param productName the name of the eaten product to update
     * @param newAmount the new amount for the eaten product
     * @return true if the eaten product's amount was successfully updated, false otherwise
     */
    public boolean updateEatenProduct(String productName, int newAmount);
}
