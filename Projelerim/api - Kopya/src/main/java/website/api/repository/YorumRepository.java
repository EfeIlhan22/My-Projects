package website.api.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import website.api.model.Yorum;

public interface  YorumRepository extends JpaRepository<Yorum, Integer> {
    
}
