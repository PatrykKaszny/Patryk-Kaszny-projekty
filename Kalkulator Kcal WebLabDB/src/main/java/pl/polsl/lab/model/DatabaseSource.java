package pl.polsl.lab.model;

import Model.EatenProduct;
import Model.Product;
import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import jakarta.persistence.Persistence;
import jakarta.persistence.PersistenceException;
import jakarta.persistence.criteria.CriteriaBuilder;
import jakarta.persistence.criteria.CriteriaQuery;
import jakarta.persistence.criteria.Root;
import java.util.List;

/**
 * Implements the DataSource interface, providing methods for interacting with
 * the database. This class uses Java Persistence API (JPA) to perform CRUD (Create, 
 * Read, Update, Delete) operations on Product and EatenProduct entities.
 * 
 * It manages an EntityManagerFactory that is used to create EntityManagers for 
 * accessing the database and performing transactions.
 * 
 * @version 1.1.0
 * @since 1.0
 * @author Patryk Kaszny
 */
public class DatabaseSource implements DataSource {

    private final EntityManagerFactory emf;

    /**
     * Initializes the DatabaseSource by creating an EntityManagerFactory based on 
     * the persistence unit "pl.polsl.lab_WebLabDB".
     */
    public DatabaseSource() {
        emf = Persistence.createEntityManagerFactory("pl.polsl.lab_WebLabDB");
    }
    
    /**
     * Persists a given object in the database. This method starts a transaction, 
     * persists the object, and commits the transaction.
     * 
     * @param object the object to be persisted in the database
     */
    @Override
    public void persistObject(Object object) {
        EntityManager em = emf.createEntityManager();
        em.getTransaction().begin();
        try {
            em.persist(object);
            em.getTransaction().commit();     
        } catch (PersistenceException e) {            
            em.getTransaction().rollback();
        } finally {
            em.close();
        }
    }

    /**
     * Retrieves the list of all products from the database.
     * 
     * @return a List of Product objects representing all products in the database
     */
    @Override
    public List<Product> getProductList() {
        EntityManager em = emf.createEntityManager();
        try {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Product> query = cb.createQuery(Product.class);
            Root<Product> root = query.from(Product.class);

            query.select(root); // Retrieves all columns from the "Product" table

            return em.createQuery(query).getResultList();
        } finally {
            em.close(); // Always close the EntityManager after use
        }
    }

    /**
     * Updates an existing product in the database.
     * 
     * @param product the Product object to update
     * @return true if the product was successfully updated, false otherwise
     */
    @Override
    public boolean update(Product product) {        
        try (EntityManager em = emf.createEntityManager()) {
            em.getTransaction().begin();
            em.merge(product);
            em.getTransaction().commit();
        } catch(Exception ex) {            
            return false;
        }        
        return true;
    }
    
    /**
     * Deletes a product from the database by its name, including any associated 
     * EatenProduct records.
     * 
     * @param name the name of the product to delete
     * @return true if the product and its associated EatenProduct records were 
     *         successfully deleted, false otherwise
     */
    @Override
    public boolean delete(String name) {
        EntityManager em = emf.createEntityManager();
        try {
            em.getTransaction().begin();

            // Delete associated EatenProduct records
            em.createQuery("DELETE FROM EatenProduct ep WHERE ep.product.name = :name")
              .setParameter("name", name)
              .executeUpdate();

            // Delete the product
            var result = em.createQuery("DELETE FROM Product p WHERE p.name = :name")
                           .setParameter("name", name)
                           .executeUpdate() != 0;
            em.getTransaction().commit();
            return result;
        } catch (Exception ex) {
            em.getTransaction().rollback();
            ex.printStackTrace();
        } finally {
            em.close();
        }
        return false;
    }

    /**
     * Retrieves the list of all eaten products from the database.
     * 
     * @return a List of EatenProduct objects representing all eaten products
     *         in the database
     */
    @Override
    public List<EatenProduct> getEatenProductList() {
        EntityManager em = emf.createEntityManager();
        try {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<EatenProduct> query = cb.createQuery(EatenProduct.class);
            Root<EatenProduct> root = query.from(EatenProduct.class);

            query.select(root); // Retrieves all columns from the "EatenProduct" table

            return em.createQuery(query).getResultList();
        } finally {
            em.close();
        }
    }

    /**
     * Updates an existing eaten product in the database.
     * 
     * @param product the EatenProduct object to update
     * @return true if the eaten product was successfully updated, false otherwise
     */
    @Override
    public boolean updateEatenProduct(EatenProduct product) {
        try (EntityManager em = emf.createEntityManager()) {
            em.getTransaction().begin();
            em.merge(product);
            em.getTransaction().commit();
        } catch(Exception ex) {            
            return false;
        }        
        return true;
    }

    /**
     * Deletes an eaten product from the database by its name.
     * 
     * @param name the name of the eaten product to delete
     * @return true if the eaten product was successfully deleted, false otherwise
     */
    @Override
    public boolean deleteEatenProduct(String name) {
        EntityManager em = emf.createEntityManager();
        try {
            em.getTransaction().begin();

            // Delete associated EatenProduct records
            int deletedCount = em.createQuery("DELETE FROM EatenProduct ep WHERE ep.product.name = :name")
                .setParameter("name", name)
                .executeUpdate();

            em.getTransaction().commit();
            return deletedCount > 0; // Return true if something was deleted
        } catch (Exception ex) {
            em.getTransaction().rollback();
            ex.printStackTrace();
        } finally {
            em.close();
        }
        return false;
    }

    /**
     * Updates the amount of a specific eaten product and recalculates its total 
     * calories based on the new amount.
     * 
     * @param productName the name of the eaten product to update
     * @param newAmount the new amount of the eaten product
     * @return true if the eaten product's amount was successfully updated, false otherwise
     */
    @Override
    public boolean updateEatenProduct(String productName, int newAmount) {
        EntityManager em = emf.createEntityManager();
        try {
            em.getTransaction().begin();

            // Find the EatenProduct associated with the given product name
            EatenProduct eatenProduct = em.createQuery("SELECT ep FROM EatenProduct ep WHERE ep.product.name = :productName", EatenProduct.class)
                                          .setParameter("productName", productName)
                                          .getSingleResult();

            if (eatenProduct != null) {
                // Update the amount of the eaten product
                eatenProduct.setAmount(newAmount);

                // Recalculate the total calories based on the new amount
                int newCalories = calculateCalories(eatenProduct.getProduct(), newAmount);
                eatenProduct.setTotalKcal(newCalories);

                // Update the EatenProduct object in the database
                em.merge(eatenProduct);

                em.getTransaction().commit();
                return true;
            }
        } catch (Exception ex) {
            em.getTransaction().rollback();
            ex.printStackTrace();
        } finally {
            em.close();
        }
        return false;
    }

    /**
     * Helper method to calculate the total calories for a given product and amount.
     * The calculation is based on the product's kcal per weight and the provided amount.
     * 
     * @param product the product whose calories need to be calculated
     * @param amount the amount of the product
     * @return the calculated total calories
     */
    private int calculateCalories(Product product, int amount) {
        double ratio = (double) amount / product.getWeight();
        return (int) (product.getKcal() * ratio);
    }
}
